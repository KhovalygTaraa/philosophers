/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 21:59:37 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/22 14:22:47 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	take_forks(t_shrmem *stat)
{
	pthread_mutex_lock(&stat->forks[stat->philo->left]);
	print_time(stat, TAKING_FORK);
	pthread_mutex_lock(&stat->forks[stat->philo->right]);
	print_time(stat, TAKING_FORK);
	stat->neighbour[stat->philo->id] = 0;
}

void	eating(t_shrmem *stat)
{
	print_time(stat, EATING);
	usleep((stat->philo->eat) * 1000);
	stat->neighbour[stat->philo->id] = stat->philo->id;
	// stat->philo->die = stat->philo->start_die;
	stat->philo->cicles--;
	pthread_mutex_unlock(&stat->forks[stat->philo->right]);
	pthread_mutex_unlock(&stat->forks[stat->philo->left]);
}

void	sleeping(t_shrmem *stat)
{
	print_time(stat, SLEEPING);
	usleep((stat->philo->sleep) * 1000);
}

void	print_time(t_shrmem *stat, int i)
{
	struct timeval	time;
	size_t		ms;

	pthread_mutex_lock(&stat->guard[3]);
	gettimeofday(&time, NULL);
	ms = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	if (i == 1)
		printf("%lums %d is thinking\n", ms - stat->time, stat->philo->id);
	else if (i == 2)
		printf("%lums %d is eating\n", ms - stat->time, stat->philo->id);
	else if (i == 3)
		printf("%lums %d is sleeping\n", ms - stat->time, stat->philo->id);
	else if (i == 4)
		printf("%lums %d has taken a fork\n", ms - stat->time, stat->philo->id);
	else if (i == 5)
	{
		printf("%lums %d is dead\n", ms - stat->time, stat->philo->id);
		return ;
	}
	pthread_mutex_unlock(&stat->guard[3]);
}