/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:41:18 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/17 19:15:05 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free_mvpair(t_mvpair *pair)
{
	if (!pair)
		return ;
	pthread_mutex_destroy(&pair->m);
	free(pair->v);
	free(pair);
}

void	free_fork_a(pthread_mutex_t *fork_a, int am)
{
	int	i;

	i = -1;
	while (++i < am)
		pthread_mutex_destroy(&fork_a[i]);
	free(fork_a);
}

void	free_info_a(t_philo_info *info_a, int am)
{
	int	i;

	i = -1;
	while (++i < am)
	{
		ft_free_mvpair(info_a[i].meals_had);
		ft_free_mvpair(info_a[i].last_meal);
	}
	free(info_a);
}

void	free_everything(pthread_t *philo_a, pthread_mutex_t *fork_a,
		t_philo_info *info_a, t_data *d)
{
	free_fork_a(fork_a, d->philo_am);
	free_info_a(info_a, d->philo_am);
	free(philo_a);
	ft_free_mvpair(d->over);
}
