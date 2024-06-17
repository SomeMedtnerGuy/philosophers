/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:47:15 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/17 19:28:48 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_over(t_mvpair *over)
{
	pthread_mutex_lock(&over->m);
	if (*(int *)over->v)
		return (pthread_mutex_unlock(&over->m), 1);
	pthread_mutex_unlock(&over->m);
	return (0);
}

int	is_somebody_dead(t_philo_info *info_a, t_data *d, int i)
{
	pthread_mutex_lock(&info_a[i].last_meal->m);
	if (ft_gettime(d->init_time) - *(int *)info_a[i].last_meal->v
		> d->time_to_die)
	{
		pthread_mutex_unlock(&info_a[i].last_meal->m);
		pthread_mutex_lock(&d->over->m);
		*(int *)d->over->v = 1;
		pthread_mutex_unlock(&d->over->m);
		usleep(1000);
		safe_printf(d, ft_gettime(d->init_time), i + 1, "died");
		return (1);
	}
	pthread_mutex_unlock(&info_a[i].last_meal->m);
	return (0);
}

void	*philo(void *argp)
{
	t_philo_info	*info;
	time_t			init_time;

	info = (t_philo_info *)argp;
	init_time = info->d->init_time;
	while (1)
	{
		if (!ft_think(info, init_time))
			return (NULL);
		if (!ft_take_forks(info, init_time))
			return (NULL);
		ft_eat(info, init_time);
		if (!ft_sleep(info, init_time))
			return (NULL);
	}
	return (NULL);
}

void	monitor(t_philo_info *info_a, t_data *d)
{
	int	i;

	i = 0;
	while (1)
	{
		if (is_somebody_dead(info_a, d, i))
			break ;
		pthread_mutex_lock(&info_a[i].meals_had->m);
		if (*(int *)info_a[i].meals_had->v >= d->meals_am_target)
			d->philo_fed++;
		else
			d->philo_fed = 0;
		pthread_mutex_unlock(&info_a[i].meals_had->m);
		if (d->meals_am_target && d->philo_fed >= d->philo_am)
		{
			pthread_mutex_lock(&d->over->m);
			*(int *)d->over->v = 1;
			pthread_mutex_unlock(&d->over->m);
			usleep(1000);
			safe_printf(d, ft_gettime(d->init_time), 0, "Everyone is fed");
			break ;
		}
		i = (i + 1) % d->philo_am;
	}
}

int	main(int argc, char **argv)
{
	pthread_t			*philo_a;
	pthread_mutex_t		*fork_a;
	t_philo_info		*info_a;
	t_data				d;
	int					i;

	if (argc != 5 && argc != 6)
		return (printf("Error parsing input. Try again\n"), 0);
	i = init_data(&d, argv, argc);
	if (i != 0)
		return (printf("Error parsing input. Try again\n"), i);
	if (alloc_arrays(&philo_a, &fork_a, &info_a, &d) != 0)
		return (errno);
	i = init_scene(philo_a, fork_a, info_a, &d);
	if (i != 0)
		return (safe_printf(&d, ft_gettime(d.init_time), 0, "Error"), i);
	monitor(info_a, &d);
	i = -1;
	while (++i < d.philo_am)
		pthread_join(philo_a[i], NULL);
	free_everything(philo_a, fork_a, info_a, &d);
	safe_printf(&d, ft_gettime(d.init_time), 0, "END OF SIMULATION");
	return (0);
}
