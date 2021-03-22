/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:08:45 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/22 15:50:16 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "two.h"

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
