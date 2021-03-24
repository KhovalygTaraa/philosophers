/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:59:39 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/24 19:27:25 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int			init_philo(t_shrmem *stat, int *val, int argc, int b)
{
	if (!(stat->philo = malloc(sizeof(t_ph))))
		return (-1);
	stat->philo->id = b + 1;
	stat->philo->start_die = val[1];
	stat->philo->die = val[1];
	stat->philo->eat = val[2];
	stat->philo->sleep = val[3];
	stat->philo->left = b;
	stat->philo->right = b + 1;
	if (pthread_mutex_init(&stat->philo->guard, NULL) != 0)
		return (-1);
	if (b + 1 == val[0])
	{
		stat->philo->right = 0;
		stat->philo->left = b;
	}
	stat->philo->cicles = -1;
	if (argc == 6)
		stat->philo->cicles = val[4];
	return (0);
}

t_shrmem	*init_env(int *v, t_init *init)
{
	t_shrmem		*new;
	int				i;

	i = 0;
	if (!(new = malloc(sizeof(t_shrmem) * (v[0]))))
		return (NULL);
	while (i != v[0])
	{
		new[i].time = chrono();
		new[i].forks = init->forks;
		new[i].guard = init->guard;
		new[i].phils = v[0];
		i++;
	}
	return (new);
}

t_init		*main_init(int *val, t_init *init)
{
	int				b;

	if (!(init->philo = malloc(sizeof(pthread_t) * val[0])))
		return (NULL);
	if (!(init->add = malloc(sizeof(pthread_t) * val[0])))
		return (NULL);
	if (!(init->guard = malloc(sizeof(pthread_mutex_t) * 10)))
		return (NULL);
	b = -1;
	while (++b != 10)
		if (pthread_mutex_init(&init->guard[b], NULL) != 0)
			return (NULL);
	if (!(init->forks = malloc(sizeof(pthread_mutex_t) * val[0])))
		return (NULL);
	b = -1;
	while (++b != val[0])
		if (pthread_mutex_init(&init->forks[b], NULL) != 0)
			return (NULL);
	return (init);
}

int			deinit(t_init *init, int *val)
{
	int		b;

	b = -1;
	while (++b < 10)
		pthread_mutex_destroy(&init->guard[b]);
	b = -1;
	while (++b < val[0])
		pthread_mutex_destroy(&init->forks[b]);
	free(val);
	free(init->philo);
	free(init->add);
	free(init->guard);
	free(init->forks);
	free(init);
	return (-1);
}
