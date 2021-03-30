/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:08:45 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/29 20:23:58 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "three.h"

int		ft_strlen(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_perror(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

int		isdigit_arg(char **argv)
{
	int		i;
	int		a;

	i = 1;
	while (argv[i] != NULL)
	{
		a = 0;
		while (argv[i][a] != '\0')
		{
			if (argv[i][a] < 48 || argv[i][a] > 57)
				return (0);
			a++;
		}
		i++;
	}
	return (1);
}

int		ft_atoi(char *str)
{
	int		res;
	int		i;
	int		a;

	i = 0;
	res = 0;
	a = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v' \
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		a = -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (a * res);
}

int		create_threads(t_init *init, t_shrmem *new, int b)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	new[b].philo->start = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	new[b].time = new[b].philo->start;
	if (pthread_create(&init->add[b], NULL, is_dead, &new[b]) != 0)
		return (-1);
	if (pthread_detach(init->add[b]) != 0)
		return (-1);
	if (pthread_create(&init->kamikadze[b], NULL, die, &new[b]) != 0)
		return (-1);
	if (pthread_detach(init->kamikadze[b]) != 0)
		return (-1);
	return (0);
}
