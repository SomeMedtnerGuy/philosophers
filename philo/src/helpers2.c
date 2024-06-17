/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:03:19 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/17 19:34:55 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	ft_gettime(time_t init_time)
{
	struct timeval	time;
	time_t			mili;

	gettimeofday(&time, NULL);
	mili = (time.tv_sec * 1000 + time.tv_usec / 1000) - init_time;
	return (mili);
}

void	*ft_memcpy(void *dest, void *src, size_t size)
{
	size_t		b;
	const char	*s;
	char		*d;

	b = 0;
	s = src;
	d = dest;
	while (b < size)
	{
		d[b] = s[b];
		b++;
	}
	return (dest);
}

void	ft_bzero(void *s, size_t n)
{
	char	*mem;

	mem = s;
	while (n != 0)
	{
		*mem = 0;
		mem++;
		n--;
	}
}

void	safe_printf(t_data *d, time_t timestamp, int philo_id, char *msg)
{
	pthread_mutex_lock(&d->printf_m);
	if (philo_id)
		printf("%lu: %i %s\n", timestamp, philo_id, msg);
	else
		printf("%lu: %s\n", timestamp, msg);
	pthread_mutex_unlock(&d->printf_m);
}
