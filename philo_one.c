/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:22:47 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/15 19:51:33 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

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

void	init(t_ph *stat, int *val, int argc)
{
	stat->phil = val[0];
	stat->die = val[1];
	stat->eat = val[2];
	stat->sleep = val[3];
	stat->cicles = -1;
	if (argc == 6)
		stat->cicles = val[4];
}

void	*philo_one(void *arg)
{
	t_ph		*stat;

	stat = arg;
	printf("%d\n", stat->id);
	free(arg);
	return (NULL);
}

int		threading(int i, pthread_t *philo, t_ph *stat, int a)
{
	t_ph	*new;
	int		b;

	b = 1;
	while (i-- != 0)
	{
		if (!(new = malloc(sizeof(t_ph))))
			return (-1);
		new->id = b;
		new->phil = stat->phil;
		new->die = stat->die;
		new->eat = stat->eat;
		new->sleep = stat->sleep;
		new->cicles = stat->cicles;
		pthread_create(&philo[i], NULL, philo_one, new);
		b++;
	}
	i = -1;
	while (++i != a)
		pthread_join(philo[i], NULL);
	return (0);
}

int		main(int argc, char **argv)
{
	pthread_t	*philo;
	int			i;
	int			*val;
	t_ph		stat;

	if (argc < 5 || 6 < argc)
	{
		ft_perror("Wrong number of arguments");
		return (-1);
	}
	if (!(val = check_args(argc, argv)))
		return (-1);
	init(&stat, val, argc);
	i = val[0];
	if (!(philo = malloc(sizeof(pthread_t) * i)))
		return (-1);
	threading(i, philo, &stat, i);
	free(philo);
	free(val);
	return (0);
}
