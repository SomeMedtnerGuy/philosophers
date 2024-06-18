/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:53:57 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/18 13:08:39 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static pthread_mutex_t	*get_fork(t_philo_info *info, int is_right)
{
	int	(*choose_fork[2])(int, int);

	choose_fork[0] = &ft_min;
	choose_fork[1] = &ft_max;
	return (&info->forks[choose_fork[(info->id + is_right) % 2](info->id,
			(info->id + 1) % info->d->philo_am)]);
}

int	ft_take_forks(t_philo_info *info, time_t init_time)
{
	pthread_mutex_lock(get_fork(info, 0));
	if (is_over(info->d->over))
		return (pthread_mutex_unlock(get_fork(info, 0)), 0);
	safe_printf(info->d, ft_gettime(init_time), info->id + 1,
		"has taken a fork");
	if (get_fork(info, 0) == get_fork(info, 1))
	{
		while (1)
		{
			if (is_over(info->d->over))
				return (pthread_mutex_unlock(get_fork(info, 0)),
					0);
		}
	}
	pthread_mutex_lock(get_fork(info, 1));
	if (is_over(info->d->over))
		return (pthread_mutex_unlock(get_fork(info, 1)),
			pthread_mutex_unlock(get_fork(info, 0)), 0);
	safe_printf(info->d, ft_gettime(init_time), info->id + 1,
		"has taken a fork");
	return (1);
}

int	ft_think(t_philo_info *info, time_t init_time)
{
	if (is_over(info->d->over))
		return (0);
	safe_printf(info->d, ft_gettime(init_time), info->id + 1, "is thinking");
	usleep(500);
	return (1);
}

int	ft_eat(t_philo_info *info, time_t init_time)
{
	if (is_over(info->d->over))
		return (0);
	pthread_mutex_lock(&info->last_meal->m);
	*(time_t *)info->last_meal->v = ft_gettime(init_time);
	pthread_mutex_unlock(&info->last_meal->m);
	safe_printf(info->d, ft_gettime(init_time), info->id + 1, "is eating");
	usleep(info->d->time_to_eat * 1000);
	pthread_mutex_unlock(get_fork(info, 1));
	pthread_mutex_unlock(get_fork(info, 0));
	pthread_mutex_lock(&info->meals_had->m);
	*(int *)info->meals_had->v += 1;
	pthread_mutex_unlock(&info->meals_had->m);
	return (1);
}

int	ft_sleep(t_philo_info *info, time_t init_time)
{
	if (is_over(info->d->over))
		return (0);
	safe_printf(info->d, ft_gettime(init_time), info->id + 1, "is sleeping");
	usleep(info->d->time_to_sleep * 1000);
	return (1);
}
