/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:21:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/08 17:56:36 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
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
	pthread_t			death_checker;
}	t_philo;

void					_check_options_(t_philo *philo);
void					_start_program_(t_philo *philo);
void					_error_(void);
void					_print_(t_pdata *dt, int task);
void					_init_each_philo_(t_pdata *pdata, int i);
void					_init_philos_(t_philo *philo);
unsigned int			_get_time_(unsigned int start);
void					*_death_checker_(void *data);
void					*_eat_checker_(void *data);
void					_death_of_ph_(t_pdata *dt);
void					*_tasks_(void *data);
void					_allocation_error_(void);
void					_clean_(t_philo *ph);
void					_init_vars_(t_philo *philo, char **argv, int argc);

#endif
