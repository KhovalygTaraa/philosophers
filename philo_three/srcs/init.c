/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:59:39 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/23 11:11:24 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "three.h"

int			init_philo(t_shrmem *stat, int *val, int argc, int b)
{
	if (!(stat->philo = malloc(sizeof(t_ph))))
		return (-1);
	stat->philo->id = b + 1;
	stat->philo->start_die = val[1];
	stat->philo->die = val[1];
	stat->philo->eat = val[2];
	stat->philo->sleep = val[3];
	stat->philo->cicles = -1;
	if (argc == 6)
		stat->philo->cicles = val[4];
	return (0);
}

t_shrmem	*init_env(int *v, t_init *init)
{
	t_shrmem		*new;
	struct timeval	time;
	int				i;

	(void)init;
	i = 0;
	if (!(new = malloc(sizeof(t_shrmem) * (v[0]))))
		return (NULL);
	gettimeofday(&time, NULL);
	while (i != v[0])
	{
		new[i].time = (time.tv_usec / 1000) + (time.tv_sec * 1000);
		new[i].forks = init->forks;
		new[i].guard1 = init->guard1;
		new[i].guard2 = init->guard2;
		new[i].phils = v[0];
		i++;
	}
	return (new);
}

t_init		*main_init(int *val, t_init *init)
{
	int		a;

	a = -1;
	if (!(init->philo = malloc(sizeof(pthread_t) * val[0])))
		return (NULL);
	if (!(init->add = malloc(sizeof(pthread_t) * val[0])))
		return (NULL);
	if ((init->guard2 = sem_open("/mm2", O_CREAT, 0644, 1)) == SEM_FAILED)
		return (NULL);
	if ((init->guard1 = sem_open("/mm1", O_CREAT, 0644, 1)) == SEM_FAILED)
		return (NULL);
	if ((init->forks = sem_open("/mm", O_CREAT, 0644, val[0])) == SEM_FAILED)
		return (NULL);
	if (sem_unlink("/mm2") == -1)
		return (NULL);
	if (sem_unlink("/mm1") == -1)
		return (NULL);
	if (sem_unlink("/mm") == -1)
		return (NULL);
	return (init);
}

int			deinit(t_init *init, int *val)
{
	free(init->philo);
	free(init->add);
	free(val);
	free(init);
	return (0);
}
