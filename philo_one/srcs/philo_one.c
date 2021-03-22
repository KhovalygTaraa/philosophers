/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:22:47 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/22 14:05:37 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		the_end;

void			*is_dead(void *arg)
{
	t_shrmem	*stat;
	struct timeval	time;
	size_t				ms;
	size_t				ms2;

	stat = arg;
	while (the_end == 0)
	{
		pthread_mutex_lock(&stat->guard[7]);
		pthread_mutex_lock(&stat->guard[9]);
		gettimeofday(&time, NULL);
		ms2 = (time.tv_usec / 1000) + (time.tv_sec * 1000);
		ms = ms2 - stat->philo->start;
		pthread_mutex_unlock(&stat->guard[9]);
		if (the_end == 1)
		{
			pthread_mutex_unlock(&stat->guard[7]);
			return (NULL);
		}
		if (ms >= stat->philo->die)
		{
			the_end = 1;
			print_time(stat, DEAD);
			printf("%zu\n", ms);
			pthread_mutex_unlock(&stat->guard[7]);
			return (NULL);
		}
		pthread_mutex_unlock(&stat->guard[7]);
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


void	*philo_one(void *arg)
{
	t_shrmem		*stat;
	struct timeval	time;

	stat = arg;

	gettimeofday(&time, NULL);
	stat->philo->start = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	while (the_end == 0 && stat->philo->cicles != 0)
	{
		// pthread_mutex_lock(&stat->guard[5]);
		// if (stat->philo->id != stat->phils && stat->philo->id != 1)
		// {
		// 	if (stat->neighbour[stat->philo->id + 1] == 0 || 
		// 	stat->neighbour[stat->philo->id - 1] == 0)
		// 	{
		// 		pthread_mutex_unlock(&stat->guard[5]);
		// 		while (stat->neighbour[stat->philo->id + 1] == 0 || 
		// 		stat->neighbour[stat->philo->id - 1] == 0)
		// 		 ;
		// 		pthread_mutex_lock(&stat->guard[5]);
		// 	}
		// }
		// else if (stat->philo->id == 1)
		// {
		// 	if (stat->neighbour[stat->philo->id + 1] == 0 || 
		// 	stat->neighbour[stat->phils] == 0)
		// 	{
		// 		pthread_mutex_unlock(&stat->guard[5]);
		// 		while (stat->neighbour[stat->philo->id + 1] == 0 || 
		// 		stat->neighbour[stat->phils] == 0)
		// 		 ;
		// 		pthread_mutex_lock(&stat->guard[5]);
		// 	}
		// }
		// else if (stat->philo->id == stat->phils)
		// {
		// 	if (stat->neighbour[stat->philo->id - 1] == 0 || 
		// 	stat->neighbour[1] == 0)
		// 	{
		// 		pthread_mutex_unlock(&stat->guard[5]);
		// 		while (stat->neighbour[stat->philo->id - 1] == 0 || 
		// 		stat->neighbour[1] == 0)
		// 		 ;
		// 		pthread_mutex_lock(&stat->guard[5]);
		// 	}
		// }
		take_forks(stat);
		// pthread_mutex_unlock(&stat->guard[5]);
		// pthread_mutex_lock(&stat->guard[9]);
		gettimeofday(&time, NULL);
		stat->philo->start = (time.tv_usec / 1000) + (time.tv_sec * 1000);
		// pthread_mutex_unlock(&stat->guard[9]);
		eating(stat);
		sleeping(stat);
		print_time(stat, THINKING);
	}
	return (NULL);
}

int		threading(t_init *init, int argc, int *val)
{
	t_shrmem	*new;
	int		b;

	if (!(new = init_env(val, init)))
		return (-1);
	b = -1;
	while (++b < val[0])
	{
		init_philo(&new[b], val, argc, b);
		pthread_create(&init->philo[b], NULL, philo_one, &new[b]);
		// usleep(50);
		pthread_detach(init->philo[b]);
		pthread_create(&init->add[b], NULL, is_dead, &new[b]);
		// usleep(50);
	}
	b = -1;
	while (++b < val[0]) 
		pthread_join(init->add[b], NULL);
	// free(new);
	return (0);
}

int		main(int argc, char **argv)
{
	int				*val;
	int				b;
	t_init			*init1;

	the_end = 0;
	b = -1;
	if (argc < 5 || 6 < argc)
		ft_perror("Wrong number of arguments");
	if (argc < 5 || 6 < argc)
		return (-1);
	if (!(val = check_args(argc, argv)))
		return (-1);
	init1 = init(val);
	threading(init1, argc, val);
	deinit(init1, val);
	free(val);
	return (0);
}
