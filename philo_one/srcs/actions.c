/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 21:59:37 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/30 14:38:44 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	take_forks(t_shrmem *stat)
{
	pthread_mutex_lock(&stat->forks[stat->philo->left]);
	print_time(stat, 0, "has taken a fork");
	if (g_the_end == 1)
		return ;
	pthread_mutex_lock(&stat->forks[stat->philo->right]);
	print_time(stat, 0, "has taken a fork");
	if (g_the_end == 1)
		return ;
}

void	eating(t_shrmem *stat)
{
	pthread_mutex_lock(&stat->philo->guard);
	print_time(stat, 0, "is eating");
	if (g_the_end == 1)
		return ;
	ft_usleep(stat->philo->eat * 1000);
	stat->philo->cicles--;
	pthread_mutex_unlock(&stat->philo->guard);
	pthread_mutex_unlock(&stat->forks[stat->philo->right]);
	pthread_mutex_unlock(&stat->forks[stat->philo->left]);
}

void	sleeping(t_shrmem *stat)
{
	print_time(stat, 0, "is sleeping");
	if (g_the_end == 1)
		return ;
	ft_usleep(stat->philo->sleep * 1000);
}

void	print_time(t_shrmem *stat, long i, char *str)
{
	long			ms1;

	pthread_mutex_lock(&stat->guard[3]);
	if (g_the_end == 1)
		return ;
	ms1 = chrono();
	printf("%ldms %d %s\n", ms1 - stat->time, stat->philo->id, str);
	if (i != 0)
	{
		g_the_end = 1;
		pthread_mutex_unlock(&stat->guard[0]);
		return ;
	}

	pthread_mutex_unlock(&stat->guard[3]);
}

int		create_phil(t_shrmem *new, int b, t_init *init)
{
	new->philo->start = chrono();
	if (pthread_create(&init->philo[b], NULL, philo_one, &new[b]) != 0)
		return (-1);
	if (pthread_detach(init->philo[b]) != 0)
		return (-1);
	if (pthread_create(&init->add[b], NULL, is_dead, &new[b]) != 0)
		return (-1);
	if (pthread_detach(init->add[b]) != 0)
		return (-1);
	return (0);
}
