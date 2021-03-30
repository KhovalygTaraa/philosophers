/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:23:39 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/29 18:15:05 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREE_H
# define THREE_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# define THINKING 1
# define EATING 2
# define SLEEPING 3
# define TAKING_FORK 4
# define DEAD 5
# define ERROR 6

typedef struct	s_ph
{
	int			id;
	int			start_die;
	size_t		die;
	int			eat;
	int			sleep;
	int			left;
	int			cicles;
	int			right;
	sem_t		*guard3;
	size_t		start;
}				t_ph;

typedef struct	s_shrmem
{
	size_t		time;
	int			phils;
	t_ph		*philo;
	sem_t		*forks;
	sem_t		*guard1;
	sem_t		*guard2;
	sem_t		*guard4;
	sem_t		*killer;
}				t_shrmem;

typedef struct	s_init
{
	sem_t		*forks;
	sem_t		*guard1;
	sem_t		*guard2;
	sem_t		*guard4;
	sem_t		*killer;
	pid_t		*philo;
	pthread_t	*add;
	pthread_t	*kamikadze;
}				t_init;

void			ft_perror(char *str);
int				ft_strlen(char *str);
int				ft_atoi(char *str);
int				isdigit_arg(char **argv);
int				init_philo(t_shrmem *stat, int *val, int argc, int b);
t_shrmem		*init_env(int *val, t_init *init);
void			take_forks(t_shrmem *stat);
void			eating(t_shrmem *stat);
void			sleeping(t_shrmem *stat);
void			thinking(t_shrmem *stat);
void			*print_time(t_shrmem *stat, int i);
t_init			*main_init(int *val, t_init *init);
int				deinit(t_init *init, int *val);
void			*die(void *arg);
void			*is_dead(void *arg);
int				create_threads(t_init *init, t_shrmem *new, int b);
void			ft_usleep(long i);

#endif
