/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:22:47 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/29 20:37:37 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "three.h"

void			*is_dead(void *arg)
{
	t_shrmem			*stat;
	struct timeval		time;
	size_t				ms;

	stat = arg;
	while (stat->philo->cicles != 0)
	{
		usleep((stat->philo->start_die) * 1000);
		gettimeofday(&time, NULL);
		ms = (time.tv_usec / 1000) + (time.tv_sec * 1000);
		if (ms - stat->philo->start >= stat->philo->die)
		{
			sem_wait(stat->philo->guard3);
			if (sem_wait(stat->guard2) == -1)
				return (print_time(stat, ERROR));
			print_time(stat, DEAD);
			if (sem_post(stat->killer) == -1)
				return (print_time(stat, ERROR));
			return (NULL);
		}
	}
	exit(1);
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

static void		*philo_three(void *arg)
{
	t_shrmem		*stat;
	struct timeval	time;

	stat = arg;
	gettimeofday(&time, NULL);
	stat->philo->start = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	while (stat->philo->cicles != 0)
	{
		take_forks(stat);
		gettimeofday(&time, NULL);
		stat->philo->start = (time.tv_usec / 1000) + (time.tv_sec * 1000);
		eating(stat);
		sleeping(stat);
		print_time(stat, THINKING);
	}
	exit(1);
}

static int		threading(t_init *init, int argc, int *val)
{
	t_shrmem		*new;
	int				b;

	if (!(new = init_env(val, init)))
		return (-1);
	b = -1;
	while (++b < val[0])
	{
		if ((init->philo[b] = fork()) == 0)
		{
			if (init_philo(&new[b], val, argc, b) == -1)
				return (-1);
			if (create_threads(init, new, b) == -1)
				return (-1);
			philo_three(&new[b]);
		}
	}
	b = -1;
	while (++b < val[0])
		if (waitpid(init->philo[b], NULL, WUNTRACED) == -1)
			exit(1);
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
		return (deinit(init, val));
	if (threading(init, argc, val) == -1)
		return (deinit(init, val));
	deinit(init, val);
	return (0);
}
