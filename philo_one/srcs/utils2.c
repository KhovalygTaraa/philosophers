/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:46:17 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/28 20:52:36 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	ft_usleep(long i)
{
	struct timeval	time;
	struct timeval	time1;

	gettimeofday(&time, NULL);
	i = i + (time.tv_sec * 1000000) + time.tv_usec;
	while (1)
	{
		usleep(1000);
		gettimeofday(&time1, NULL);
		if ((time1.tv_sec * 1000000) + time1.tv_usec > i)
			break ;
	}
}

int		double_threads(int *val, t_shrmem *new, t_init *init, int argc)
{
	int		b;

	b = 0;
	while (b < val[0])
	{
		if (init_philo(&new[b], val, argc, b) == -1)
			return (-1);
		create_phil(new, b, init);
		b += 2;
	}
	usleep(100);
	b = 1;
	while (b < val[0])
	{
		if (init_philo(&new[b], val, argc, b) == -1)
			return (-1);
		create_phil(new, b, init);
		b += 2;
	}
	return (0);
}
