/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:21:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/14 16:19:01 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "../libft/libft.h"

# define MAX_INT 2147483647
# define FORK 4
# define EAT 5
# define SLEEP 6
# define THINK 7

typedef struct s_pdata
{
	int				name;
	int				nbr_eatings;
	int				l_fork;
	int				r_fork;
	unsigned int	limit;
	sem_t			*ph;
	pid_t			pid;
	struct s_philo	*philo;
}					t_pdata;

typedef struct s_philo
{
	char				**options;
	int					int_options[5];
	int					nbr_ps;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					is_alive;
	int					nbr_peat;
	int					error;
	int					nbr_opt;
	int					end_sim;
	int					nbr_philos_meat;
	unsigned int		start_time;
	t_pdata				*pdata;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		p_hold;
	pthread_t			eat_checker;
	sem_t				*forks_b;
	sem_t				*print_b;
	sem_t				*p_hold_b;
	sem_t				*eat_b;
	pthread_t			death_checker;
}	t_philo;

void					_init_each_philo_sem_(t_pdata *pd, \
	int i, int nbr_philos);
int						_create_semaphore_(const char *sem_name, \
	int val, sem_t **sem);
int						_check_options_(t_philo *philo);
int						_semaphores_(t_philo *phil);
int						_start_program_(t_philo *philo);
int						_error_(void);
void					_print_(t_pdata *dt, int task);
void					_init_each_philo_(t_pdata *pdata, int i);
int						_init_philos_(t_philo *philo);
unsigned int			_get_time_(unsigned int start);
void					*_death_checker_(void *data);
void					*_eat_checker_(void *data);
void					_death_of_ph_(t_pdata *dt);
void					*_tasks_(void *data);
int						_allocation_error_(void);
void					_clean_(t_philo *ph);
void					_init_vars_(t_philo *philo, char **argv, int argc);

#endif
