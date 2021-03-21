/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:22:47 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/21 20:47:54 by swquinc          ###   ########.fr       */
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
		pthread_mutex_lock(&stat->guard[9]);
		if (the_end == 1)
			return (NULL);
		gettimeofday(&time, NULL);
		ms2 = (time.tv_usec / 1000) + (time.tv_sec * 1000);
		ms = stat->philo->start - ms2;
		if (ms >= stat->philo->die)
		{
			the_end = 1;
			print_time(stat, DEAD);
			pthread_mutex_unlock(&stat->guard[9]);
			return (NULL);
		}
		pthread_mutex_unlock(&stat->guard[9]);
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
	static int		flag;
	struct timeval	time;
	size_t	ms;
	size_t	ms1;

	stat = arg;

	gettimeofday(&time, NULL);
	stat->philo->start = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	while (the_end == 0 && stat->philo->cicles != 0)
	{
		// usleep(10000);
		// pthread_mutex_lock(&stat->guard[4]);
		// if (flag == 1)
		// {
		// 	pthread_mutex_unlock(&stat->guard[4]);
		// 	break ;
		// }
		take_forks(stat);
		gettimeofday(&time, NULL);
		stat->philo->start = (time.tv_usec / 1000) + (time.tv_sec * 1000); 	
		// if (flag == 1)
		// {
		// 	pthread_mutex_unlock(&stat->forks[stat->philo->right]);
		// 	pthread_mutex_unlock(&stat->forks[stat->philo->left]);
		// 	break ;
		// }
		// if (stat->philo->die <= 0)
		// {
		// 	print_time(stat, DEAD);
		// 	flag = 1;
		// 	pthread_mutex_unlock(&stat->forks[stat->philo->right]);
		// 	pthread_mutex_unlock(&stat->forks[stat->philo->left]);
		// 	break ;
		// }
		eating(stat);
		sleeping(stat);
		print_time(stat, THINKING);
		// stat->philo->die -= stat->philo->sleep;
	}
	return (NULL);
}

int		threading(t_init *init, int argc, int *val)
{
	t_shrmem	*new;
	int		b;

	if (!(new = init_env(val, init->forks, init->guard)))
		return (-1);
	b = -1;
	while (++b < val[0])
	{
		init_philo(&new[b], val, argc, b);
		pthread_create(&init->philo[b], NULL, philo_one, &new[b]);
		pthread_detach(init->philo[b]);
		pthread_create(&init->add[b], NULL, is_dead, &new[b]);
		usleep(3000);
	}
	b = -1;
	while (++b < val[0]) 
		pthread_join(init->add[b], NULL);
	free(new);
	return (0);
}

int		main(int argc, char **argv)
{
	int				*val;
	int				b;
	t_init			*init1;

	b = -1;
	if (argc < 5 || 6 < argc)
		ft_perror("Wrong number of arguments");
	if (argc < 5 || 6 < argc)
		return (-1);
	if (!(val = check_args(argc, argv)))
		return (-1);
	init1 = init(val);
	threading(init1, argc, val);
	b = -1;
	deinit(init1, val);
	free(val);
	return (0);
}
