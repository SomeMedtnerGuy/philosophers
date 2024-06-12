/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:24 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/12 20:27:53 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h> //for size_t
# include <stdio.h> //for printf()
# include <stdlib.h> //for exit()
# include <unistd.h> //for sleep()
# include <pthread.h> //for threads
# include <sys/time.h> //for gettimeofday()

typedef struct s_mvpair
{
	pthread_mutex_t	m;
	void	*v;
}	t_mvpair;

typedef struct s_data
{
	int	philo_am;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	time_t	init_time;
	t_mvpair	*over;
}	t_data;

typedef struct s_philo_info
{
	int	id;
	t_data	*d;
	pthread_mutex_t	*forks;
	t_mvpair	*last_meal;
}	t_philo_info;

#endif
