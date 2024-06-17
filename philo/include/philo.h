/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:48:24 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/17 19:01:18 by ndo-vale         ###   ########.fr       */
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
# include <errno.h> //for errno

typedef struct s_mvpair
{
	pthread_mutex_t	m;
	void			*v;
}	t_mvpair;

typedef struct s_data
{
	int				philo_am;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meals_am_target;
	time_t			init_time;
	t_mvpair		*over;
	int				philo_fed;
	pthread_mutex_t	printf_m;
}	t_data;

typedef struct s_philo_info
{
	int				id;
	t_data			*d;
	pthread_mutex_t	*forks;
	t_mvpair		*last_meal;
	t_mvpair		*meals_had;
}	t_philo_info;

time_t		ft_atoti(char *nbr);
int			ft_atoi(char *nbr);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_min(int a, int b);
int			ft_max(int a, int b);
void		ft_bzero(void *s, size_t n);
void		safe_printf(t_data *d, time_t timestamp, int philo_id, char *msg);
int			init_data(t_data *d, char **argv, int argc);
int			alloc_arrays(pthread_t **philo_a, pthread_mutex_t **fork_a,
				t_philo_info **info_a, t_data *d);
time_t		ft_gettime(time_t init_time);
void		*ft_memcpy(void *dest, void *src, size_t size);
t_mvpair	*init_mvpair(void *data, size_t data_size, int *status);
void		ft_free_mvpair(t_mvpair *pair);
void		free_fork_a(pthread_mutex_t *fork_a, int am);
void		free_info_a(t_philo_info *info_a, int am);
void		free_everything(pthread_t *philo_a, pthread_mutex_t *fork_a,
				t_philo_info *info_a, t_data *d);
int			init_scene(pthread_t *philo_, pthread_mutex_t *fork_a,
				t_philo_info *info_a, t_data *d);
void		*philo(void *argp);
int			is_over(t_mvpair *over);
int			is_somebody_dead(t_philo_info *info_a, t_data *d, int i);
int			ft_take_forks(t_philo_info *info, time_t init_time);
int			ft_think(t_philo_info *info, time_t init_time);
void		ft_eat(t_philo_info *info, time_t init_time);
int			ft_sleep(t_philo_info *info, time_t init_time);

#endif
