/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:59:39 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/21 20:33:33 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	init_philo(t_shrmem *stat, int *val, int argc, int b)
{
	if (!(stat->philo = malloc(sizeof(t_ph))))
		return ;
	stat->philo->id = b + 1;
	stat->philo->start_die = val[1];
	stat->philo->die = val[1];
	stat->philo->eat = val[2];
	stat->philo->sleep = val[3];
	stat->philo->left = b;
	stat->philo->right = b + 1;
	if (b + 1 == val[0])
	{
		stat->philo->right = b;
		stat->philo->left = 0;
	}
	stat->philo->cicles = -1;
	if (argc == 6)
		stat->philo->cicles = val[4];
}


t_shrmem	*init_env(int *v, pthread_mutex_t *f, pthread_mutex_t *g)
{
	t_shrmem		*new;
	struct timeval	time;
	int				i;

	i = 0;
	if (!(new = malloc(sizeof(t_shrmem) * (v[0]))))
		return (NULL);
	gettimeofday(&time, NULL);
	while (i != v[0])
	{
		new[i].time = (time.tv_usec / 1000) + (time.tv_sec * 1000);
		new[i].forks = f;
		new[i].guard = g;
		i++;
	}
	return (new);
}

t_init		*init(int *val)
{
	int				b;
	t_init			*init;

	b = -1;
	if (!(init = malloc(sizeof(t_init))))
		return (NULL);
	if (!(init->philo = malloc(sizeof(pthread_t) * val[0])))
		return (NULL);
	if (!(init->add = malloc(sizeof(pthread_t) * val[0])))
		return (NULL);
	if (!(init->guard = malloc(sizeof(pthread_mutex_t) * 10)))
		return (NULL);
	while (++b != 10)
		pthread_mutex_init(&init->guard[b], NULL);
	if (!(init->forks = malloc(sizeof(pthread_mutex_t) * val[0])))
		return (NULL);
	b = -1;
	while (++b != val[0])
		pthread_mutex_init(&init->forks[b], NULL);
	return (init);
}

void		deinit(t_init *init, int *val)
{
	int		b;

	b = -1;
	while (++b < 10)
		pthread_mutex_destroy(&init->guard[b]);
	free(init->philo);
	free(init->add);
	free(init->guard);
	b = -1;
	while (++b < val[0])
		pthread_mutex_destroy(&init->forks[b]);
	free(init->forks);
	free(init);
}
