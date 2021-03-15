/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:23:39 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/15 19:42:51 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ONE_H
# define ONE_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct	s_ph
{
	int		id;
	int		phil;
	int		die;
	int		eat;
	int		sleep;
	int		cicles;
}				t_ph;

void	ft_perror(char *str);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
int		isdigit_arg(char **argv);

#endif
