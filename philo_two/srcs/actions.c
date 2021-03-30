/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 21:59:37 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/29 21:39:57 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "two.h"

void	take_forks(t_shrmem *stat)
{
	sem_wait(stat->guard3);
	sem_wait(stat->forks);
	print_time(stat, TAKING_FORK);
	sem_wait(stat->forks);
	print_time(stat, TAKING_FORK);
	sem_post(stat->guard3);
}

void	eating(t_shrmem *stat)
{
	sem_wait(stat->philo->et);
	print_time(stat, EATING);
	ft_usleep((stat->philo->eat) * 1000);
	stat->philo->cicles--;
	sem_post(stat->philo->et);
	sem_post(stat->forks);
	sem_post(stat->forks);
}

void	sleeping(t_shrmem *stat)
{
	print_time(stat, SLEEPING);
	ft_usleep((stat->philo->sleep) * 1000);
}

void	*print_time(t_shrmem *stat, int i)
{
	struct timeval	time;
	size_t			ms;

	sem_wait(stat->guard1);
	gettimeofday(&time, NULL);
	ms = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	if (i == 1)
		printf("%zums %d is thinking\n", ms - stat->time, stat->philo->id);
	else if (i == 2)
		printf("%zums %d is eating\n", ms - stat->time, stat->philo->id);
	else if (i == 3)
		printf("%zums %d is sleeping\n", ms - stat->time, stat->philo->id);
	else if (i == 4)
		printf("%zums %d has taken a fork\n", ms - stat->time, stat->philo->id);
	if (i == 5)
	{
		printf("%zums %d died\n", ms - stat->time, stat->philo->id);
		return (NULL);
	}
	sem_post(stat->guard1);
	return (NULL);
}
