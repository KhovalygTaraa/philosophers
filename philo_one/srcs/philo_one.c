/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:22:47 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/30 14:37:39 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void			*is_dead(void *arg)
{
	t_shrmem			*stat;
	long				ms;

	stat = arg;
	while (stat->philo->cicles != 0)
	{
		usleep(stat->philo->start_die * 1000);
		ms = chrono();
		if (ms - stat->philo->start >= stat->philo->die)
		{
			pthread_mutex_lock(&stat->guard[7]);
			pthread_mutex_lock(&stat->philo->guard);
			if (stat->philo->cicles == 0)
			{
				pthread_mutex_lock(&stat->guard[3]);
				pthread_mutex_unlock(&stat->guard[0]);
			}
			else
				print_time(stat, ms, "died");
			return (NULL);
		}
	}
	return (NULL);
}

static int		*check_args(int argc, char **argv)
{
	int		*val;
	int		i;

	i = -1;
	if (!isdigit_arg(argv))
	{
		ft_perror("Error: invalid value");
		return (NULL);
	}
	if (!(val = malloc(sizeof(int) * (argc - 1))))
	{
		ft_perror("Error: malloc error");
		return (NULL);
	}
	while (++i != (argc - 1))
	{
		val[i] = ft_atoi(argv[i + 1]);
		if (val[i] <= 0)
		{
			ft_perror("Error: invalid value");
			free(val);
			return (NULL);
		}
	}
	return (val);
}

void			*philo_one(void *arg)
{
	t_shrmem		*stat;

	stat = arg;
	stat->philo->start = chrono();
	while (stat->philo->cicles != 0)
	{
		take_forks(stat);
		if (g_the_end == 1)
			return (NULL);
		stat->philo->start = chrono();
		eating(stat);
		if (g_the_end == 1)
			return (NULL);
		sleeping(stat);
		if (g_the_end == 1)
			return (NULL);
		print_time(stat, 0, "is thinking");
		if (g_the_end == 1)
			return (NULL);
	}
	return (NULL);
}

static int		threading(t_init *init, int argc, int *val)
{
	t_shrmem	*new;
	int			b;

	pthread_mutex_lock(&init->guard[0]);
	g_the_end = 0;
	if (!(new = init_env(val, init)))
		return (-1);
	if (double_threads(val, new, init, argc) == -1)
		return (-1);
	pthread_mutex_lock(&init->guard[0]);
	b = -1;
	while (++b < val[0])
	{
		pthread_mutex_destroy(&new[b].philo->guard);
		free(new[b].philo);
	}
	free(new);
	return (0);
}

int				main(int argc, char **argv)
{
	int				*val;
	int				b;
	t_init			*init;

	b = -1;
	if (argc < 5 || 6 < argc)
		ft_perror("Wrong number of arguments");
	if (argc < 5 || 6 < argc)
		return (-1);
	if (!(val = check_args(argc, argv)))
		return (-1);
	if (!(init = malloc(sizeof(t_init))))
		return (deinit(init, val));
	if (!(init = main_init(val, init)))
		return (deinit(init, val));
	if (threading(init, argc, val) == -1)
		return (deinit(init, val));
	deinit(init, val);
	return (0);
}
