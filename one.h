/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:23:39 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/21 20:33:24 by swquinc          ###   ########.fr       */
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
# include <errno.h>
# define THINKING 1
# define EATING 2
# define SLEEPING 3
# define TAKING_FORK 4
# define DEAD 5

typedef struct	s_ph
{
	int		id;
	int		nid1;
	int		nid2;
	int		start_die;
	int		die;
	int		eat;
	int		sleep;
	int		left;
	int		cicles;
	int		right;
	size_t	start;
}				t_ph;

typedef struct	s_shrmem
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		*guard;
	size_t				time;
	t_ph				*philo;
}				t_shrmem;

typedef struct	s_init
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		*guard;
	pthread_t			*philo;
	pthread_t			*add;
}				t_init;

void		ft_perror(char *str);
int			ft_strlen(char *str);
int			ft_atoi(char *str);
int			isdigit_arg(char **argv);
void		init_philo(t_shrmem *stat, int *val, int argc, int b);
t_shrmem	*init_env(int *val, pthread_mutex_t *f, pthread_mutex_t *g);
void		take_forks(t_shrmem *stat);
size_t		eating(t_shrmem *stat);
void		sleeping(t_shrmem *stat);
void		print_time(t_shrmem *stat, int i);
t_init		*init(int *val);
void		deinit(t_init *init, int *val);

#endif
