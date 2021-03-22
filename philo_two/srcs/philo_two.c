/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:22:47 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/23 01:11:28 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "two.h"

static void		*is_dead(void *arg)
{
	t_shrmem			*stat;
	struct timeval		time;
	size_t				ms;

	stat = arg;
	while (g_the_end == 0 && stat->philo->cicles != 0)
	{
		sem_wait(stat->guard2);
		gettimeofday(&time, NULL);
		ms = (time.tv_usec / 1000) + (time.tv_sec * 1000) - stat->philo->start;
		if (g_the_end == 1)
		{
			sem_post(stat->guard2);
			return (NULL);
		}
		if (ms >= stat->philo->die)
		{
			g_the_end = 1;
			print_time(stat, DEAD);
			sem_post(stat->guard2);
			return (NULL);
		}
		sem_post(stat->guard2);
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

static void		*philo_two(void *arg)
{
	t_shrmem		*stat;
	struct timeval	time;

	stat = arg;
	gettimeofday(&time, NULL);
	stat->philo->start = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	while (g_the_end == 0 && stat->philo->cicles != 0)
	{
		take_forks(stat);
		gettimeofday(&time, NULL);
		stat->philo->start = (time.tv_usec / 1000) + (time.tv_sec * 1000);
		eating(stat);
		sleeping(stat);
		print_time(stat, THINKING);
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
	{
		if (init_philo(&new[b], val, argc, b) == -1)
			return (-1);
		if (pthread_create(&init->philo[b], NULL, philo_two, &new[b]) != 0)
			return (-1);
		if (pthread_detach(init->philo[b]) != 0)
			return (-1);
		if (pthread_create(&init->add[b], NULL, is_dead, &new[b]) != 0)
			return (-1);
	}
	b = -1;
	while (++b < val[0])
		if (pthread_join(init->add[b], NULL) != 0)
			return (-1);
	free(new);
	return (0);
}

int				main(int argc, char **argv)
{
	int				*val;
	t_init			*init;

	if (argc < 5 || 6 < argc)
		ft_perror("Wrong number of arguments");
	if (argc < 5 || 6 < argc)
		return (-1);
	if (!(val = check_args(argc, argv)))
		return (-1);
	if (!(init = malloc(sizeof(t_init))))
		return (-1);
	if (!(main_init(val, init)))
	{
		deinit(init, val);
		return (-1);
	}
	if (threading(init, argc, val) == -1)
	{
		deinit(init, val);
		return (-1);
	}
	if (deinit(init, val) == -1)
		return (-1);
	return (0);
}
