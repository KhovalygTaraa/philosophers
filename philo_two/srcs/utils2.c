/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:46:17 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/29 19:49:56 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "two.h"

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

int		unlink_sem(void)
{
	if (sem_unlink("/mm9") == -1)
		return (-1);
	if (sem_unlink("/mm6") == -1)
		return (-1);
	if (sem_unlink("/mm1") == -1)
		return (-1);
	if (sem_unlink("/mm") == -1)
		return (-1);
	return (0);
}
