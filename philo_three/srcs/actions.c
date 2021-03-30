/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 21:59:37 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/29 21:50:23 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "three.h"

void	take_forks(t_shrmem *stat)
{
	sem_wait(stat->guard4);
	if (sem_wait(stat->forks) == -1)
		print_time(stat, ERROR);
	print_time(stat, TAKING_FORK);
	if (sem_wait(stat->forks) == -1)
		print_time(stat, ERROR);
	print_time(stat, TAKING_FORK);
	sem_post(stat->guard4);
}

void	eating(t_shrmem *stat)
{
	sem_wait(stat->philo->guard3);
	print_time(stat, EATING);
	ft_usleep((stat->philo->eat) * 1000);
	stat->philo->cicles--;
	sem_post(stat->philo->guard3);
	if (sem_post(stat->forks) == -1)
		print_time(stat, ERROR);
	if (sem_post(stat->forks) == -1)
		print_time(stat, ERROR);
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
	else if (i == 5)
		printf("%zums %d died\n", ms - stat->time, stat->philo->id);
	else if (i == 6)
	{
		printf("%s\n", "System error");
		sem_post(stat->killer);
	}
	if (i == 5 || i == 6)
		return (NULL);
	sem_post(stat->guard1);
	return (NULL);
}

void	*die(void *arg)
{
	t_shrmem		*stat;

	stat = arg;
	sem_wait(stat->killer);
	sem_post(stat->killer);
	exit(1);
}
