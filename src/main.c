/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:47:15 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/12 22:46:27 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Access philosophers's forks as fork[philoi] AND fork[philoi+1 % philo_am]

#include "../include/philo.h"

time_t	ft_atoti(char *nbr)
{
	time_t	ti;

	ti = 0;
	while (*nbr >= '0' && *nbr <= '9')
	{
		ti = ti * 10 + (*nbr - '0');
		if (ti < 0)
			return (0);
		nbr++;
	}
	return (ti);
}

int	ft_atoi(char *nbr)
{
	int	i;

	i = 0;
	while (*nbr >= '0' && *nbr <= '9')
	{
		i = i * 10 + (*nbr - '0');
		if (i < 0)
			return (0);
		nbr++;
	}
	return (i);
}

int	init_data(t_data *d, char **argv)
{
	struct timeval	time;
	int	*over_flag;

	gettimeofday(&time, NULL);
	d->philo_am = ft_atoi(argv[1]);
	d->time_to_die = ft_atoti(argv[2]);
	d->time_to_eat = ft_atoti(argv[3]);
	d->time_to_sleep = ft_atoti(argv[4]);
	d->init_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	d->over = (t_mvpair *)malloc(sizeof(t_mvpair));
	pthread_mutex_init(&(d->over->m), NULL);
	over_flag = (int *)malloc(sizeof(int));
	*over_flag = 0;
	d->over->v = (void *)over_flag;

	if (d->philo_am == 0 || d->time_to_die == 0
			|| d->time_to_eat == 0
			|| d->time_to_sleep == 0)
		return (-1);
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	total_size;

	if (nmemb * size == 0 || SIZE_MAX / nmemb < size)
		return ((void *)malloc(0));
	total_size = nmemb * size;
	ptr = (char *)malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	while (total_size--)
		ptr[total_size] = 0;
	return ((void *)ptr);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

time_t	ft_gettime(time_t init_time)
{
	struct timeval	time;
	time_t	mili;

	gettimeofday(&time, NULL);
        mili = (time.tv_sec * 1000 + time.tv_usec / 1000) - init_time;
	return (mili);
}

void	*philo(void *argp)
{
	t_philo_info	*info;
	time_t	init_time;

	info = (t_philo_info *)argp;
	init_time = info->d->init_time;
	while (1)
	{
		pthread_mutex_lock(&info->d->over->m);
		if (*(int *)info->d->over->v)
			return (pthread_mutex_unlock(&info->d->over->m), NULL);
		pthread_mutex_unlock(&info->d->over->m);
		printf("%lu: %i is thinking\n", ft_gettime(init_time), info->id + 1);
		pthread_mutex_lock(&info->forks[ft_min(info->id, 
					(info->id + 1) % info->d->philo_am)]);
		pthread_mutex_lock(&info->d->over->m);
		if (*(int *)info->d->over->v)
		{
			pthread_mutex_unlock(&info->forks[ft_min(info->id, 
						(info->id + 1) % info->d->philo_am)]);
			return (pthread_mutex_unlock(&info->d->over->m), NULL);
		}
		pthread_mutex_unlock(&info->d->over->m);
		printf("%lu: %i has taken a fork\n", ft_gettime(init_time), info->id + 1);
		pthread_mutex_lock(&info->forks[ft_max(info->id, 
					(info->id + 1) % info->d->philo_am)]);
		pthread_mutex_lock(&info->d->over->m);
		if (*(int *)info->d->over->v)
                {
			pthread_mutex_unlock(&info->d->over->m);
                        pthread_mutex_unlock(&info->forks[ft_max(info->id,
                                                (info->id + 1) % info->d->philo_am)]);
                        pthread_mutex_unlock(&info->forks[ft_min(info->id,
                                        (info->id + 1) % info->d->philo_am)]);
			return (NULL);
                }
		pthread_mutex_unlock(&info->d->over->m);
                printf("%lu: %i has taken a fork\n", ft_gettime(init_time), info->id + 1);
		pthread_mutex_lock(&info->last_meal->m);
                *(time_t *)info->last_meal->v = ft_gettime(init_time);
                pthread_mutex_unlock(&info->last_meal->m);
		printf("%lu: %i is eating\n", ft_gettime(init_time), info->id + 1);
		usleep(info->d->time_to_eat * 1000);
		pthread_mutex_unlock(&info->forks[ft_max(info->id,
					(info->id + 1) % info->d->philo_am)]);
		pthread_mutex_unlock(&info->forks[ft_min(info->id,
					(info->id + 1) % info->d->philo_am)]);
		pthread_mutex_lock(&info->d->over->m);
                if (*(int *)info->d->over->v)
                        return (pthread_mutex_unlock(&info->d->over->m), NULL);
                pthread_mutex_unlock(&info->d->over->m);
		printf("%lu: %i is sleeping\n", ft_gettime(init_time), info->id + 1);
		usleep(info->d->time_to_sleep * 1000);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t		*philo_a;
	pthread_mutex_t		*fork_a;
	t_philo_info		*info_a;
	t_data	d;
	int	i;

	if (argc != 5 && argc != 6)
		return (printf("Provide correct number of arguments plz\n"), 0);
	if (init_data(&d, argv) != 0)
		return (printf("Provide ACTUAL numbers plz\n"), 0);
	philo_a = (pthread_t *)ft_calloc(d.philo_am, sizeof(pthread_t));
	fork_a = (pthread_mutex_t *)ft_calloc(d.philo_am, sizeof(pthread_mutex_t));
	info_a = (t_philo_info *)ft_calloc(d.philo_am, sizeof(t_philo_info));
	if (!philo_a || !fork_a || !info_a)
		return (free(philo_a), free(fork_a), 0);
	i = -1;
	while (++i < d.philo_am)
	{
		info_a[i].id = i;
		info_a[i].d = &d;
		info_a[i].forks = fork_a;
		info_a[i].last_meal = (t_mvpair *)ft_calloc(1, sizeof(t_mvpair));
		pthread_mutex_init(&info_a[i].last_meal->m, NULL);
		info_a[i].last_meal->v = (void *)ft_calloc(1, sizeof(int));
		*(int *)info_a[i].last_meal->v = 0;
		pthread_mutex_init(&fork_a[i], NULL);
	}
	i = -1;
	while (++i < d.philo_am)
		pthread_create(&philo_a[i], NULL, &philo, &info_a[i]);
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&info_a[i].last_meal->m);
		if (ft_gettime(d.init_time) - *(int *)info_a[i].last_meal->v > d.time_to_die)
		{
			pthread_mutex_unlock(&info_a[i].last_meal->m);
			pthread_mutex_lock(&d.over->m);
			*(int *)d.over->v = 1;
			pthread_mutex_unlock(&d.over->m);
			printf("%lu: PHILOSOPHER NO. %i HAS DIED OMGGGGG\n",
					ft_gettime(d.init_time), i + 1);
			break ;
		}
		pthread_mutex_unlock(&info_a[i].last_meal->m);
		i = (i + 1) % d.philo_am;
	}
	i = -1;
	while (++i < d.philo_am)
		pthread_join(philo_a[i], NULL);
	printf("Reached");
	return (0);
}
