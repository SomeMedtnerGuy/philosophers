/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:58:03 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/18 09:18:54 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_philos(pthread_t *philo_a, t_philo_info *info_a, t_data *d)
{
	int	i;
	int	j;
	int	error;

	i = -1;
	error = 0;
	while (++i < d->philo_am)
	{
		error = pthread_create(&philo_a[i], NULL, &philo, &info_a[i]);
		if (error)
		{
			j = -1;
			while (++j < i)
				return (pthread_detach(philo_a[j]), error);
		}
	}
	return (error);
}

int	init_scene(pthread_t *philo_a, pthread_mutex_t *fork_a,
		t_philo_info *info_a, t_data *d)
{
	int	i;
	int	error;

	error = 0;
	i = -1;
	while (++i < d->philo_am)
	{
		info_a[i].id = i;
		info_a[i].d = d;
		info_a[i].forks = fork_a;
		info_a[i].meals_had = init_mvpair(NULL, sizeof(int), &error);
		if (error)
			return (free_fork_a(fork_a, i), free_info_a(info_a, i), error);
		info_a[i].last_meal = init_mvpair(NULL, sizeof(time_t), &error);
		if (error)
			return (free_fork_a(fork_a, i), free_info_a(info_a, i),
				ft_free_mvpair(info_a[i].meals_had), error);
		error = pthread_mutex_init(&fork_a[i], NULL);
		if (error)
			return (free_fork_a(fork_a, i), free_info_a(info_a, i + 1), error);
	}
	error = init_philos(philo_a, info_a, d);
	if (error)
		return (free_fork_a(fork_a, i + 1), free_info_a(info_a, i + 1), error);
	return (0);
}

int	init_data(t_data *d, char **argv, int argc)
{
	struct timeval	time;
	int				status;

	gettimeofday(&time, NULL);
	d->philo_am = ft_atoi(argv[1]);
	d->time_to_die = ft_atoti(argv[2]);
	d->time_to_eat = ft_atoti(argv[3]);
	d->time_to_sleep = ft_atoti(argv[4]);
	status = pthread_mutex_init(&d->printf_m, NULL);
	if (status != 0)
		return (-1);
	if (argc == 6)
	{
		d->meals_am_target = ft_atoi(argv[5]);
		if (d->meals_am_target == 0)
			return (pthread_mutex_destroy(&d->printf_m), 0);
	}
	else
		d->meals_am_target = -2;
	d->init_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	d->over = init_mvpair(NULL, sizeof(int), &status);
	if (d->philo_am <= 0 || d->time_to_die == 0 || d->time_to_eat == 0
		|| d->time_to_sleep == 0 || d->meals_am_target == -1 || status != 0)
		return (ft_free_mvpair(d->over), -1);
	return (0);
}

int	alloc_arrays(pthread_t **philo_a, pthread_mutex_t **fork_a,
		t_philo_info **info_a, t_data *d)
{
	*philo_a = (pthread_t *)ft_calloc(d->philo_am, sizeof(pthread_t));
	*fork_a = (pthread_mutex_t *)ft_calloc(d->philo_am,
			sizeof(pthread_mutex_t));
	*info_a = (t_philo_info *)ft_calloc(d->philo_am, sizeof(t_philo_info));
	if (!*philo_a || !*fork_a || !*info_a)
		return (free(*philo_a), free(*fork_a), free(*info_a), errno);
	return (0);
}

t_mvpair	*init_mvpair(void *data, size_t data_size, int *status)
{
	t_mvpair	*pair;

	pair = (t_mvpair *)ft_calloc(1, sizeof(t_mvpair));
	if (!pair)
		return (*status = errno, NULL);
	*status = pthread_mutex_init(&pair->m, NULL);
	if (*status != 0)
		return (free(pair), NULL);
	pair->v = (void *)ft_calloc(1, data_size);
	if (!pair->v)
		return (pthread_mutex_destroy(&pair->m),
			free(pair), NULL);
	if (data)
		ft_memcpy(pair->v, data, data_size);
	else
		ft_bzero(pair->v, data_size);
	return (pair);
}
