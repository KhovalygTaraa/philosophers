/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:22:47 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/24 19:33:41 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

static void		*is_dead(void *arg)
{
	t_shrmem			*stat;
	long				ms;

	stat = arg;
	while (g_the_end == 0 && stat->philo->cicles != 0)
	{
		ms = chrono() - stat->philo->start;
		pthread_mutex_lock(&stat->philo->guard);
		pthread_mutex_lock(&stat->guard[7]);
		if (g_the_end == 1)
		{
			pthread_mutex_unlock(&stat->guard[7]);
			return (NULL);
		}
		if (ms > stat->philo->die)
		{
			g_the_end = 1;
			print_time(stat, 1, "died");
			pthread_mutex_unlock(&stat->guard[7]);
			return (NULL);
		}
		pthread_mutex_unlock(&stat->guard[7]);
		pthread_mutex_unlock(&stat->philo->guard);
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

static void		*philo_one(void *arg)
{
	t_shrmem		*stat;

	stat = arg;
	stat->philo->start = chrono();
	while (stat->philo->cicles != 0)
	{
		take_forks(stat);
		stat->philo->start = chrono();
		eating(stat);
		sleeping(stat);
		stat->philo->die = stat->philo->die + (chrono() -
		stat->philo->start - stat->philo->sleep - stat->philo->eat);
		print_time(stat, 0, "is thinking");
	}
	return (NULL);
}

static int		threading(t_init *init, int argc, int *val)
{
	t_shrmem	*new;
	int			b;

	g_the_end = 0;
	if (!(new = init_env(val, init)))
		return (-1);
	b = -1;
	while (++b < val[0])
		create_phil(new, b, init);
	b = -1;
	while (++b < val[0])
		if (pthread_join(init->add[b], NULL) != 0)
			return (-1);
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
