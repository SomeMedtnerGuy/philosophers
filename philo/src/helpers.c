/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:54:40 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/18 08:57:19 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (*nbr != '\0')
		return (0);
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
			return (-1);
		nbr++;
	}
	if (*nbr != '\0')
		return (-1);
	return (i);
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
