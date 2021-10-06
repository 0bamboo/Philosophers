/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:21:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/06 18:52:21 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILOSOPHERS_H

#define _PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include "../libft/libft.h"

# define MAX_INT 2147483647


typedef struct s_pdata
{
	int	name;
	int	nbr_eatings;
	int	l_fork;
	int	r_fork;
	unsigned int	limit;
	struct s_philo *philo;
}				t_pdata;

typedef struct	s_philo
{
	char				**options;
	int					int_options[5];
	int					nbr_ps;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					nbr_peat;
	int					error;
	int					nbr_opt;
	unsigned int 		start_time;
	t_pdata				*pdata;
	pthread_mutex_t		*forks;
}				t_philo;

void			_check_options_(t_philo *philo);
void			_start_program_(t_philo *philo);
void			_error_();
void 			_init_each_philo_(t_pdata *pdata, int i);
void			_init_philos_(t_philo *philo);
unsigned int	_get_time_(unsigned int start);
void			_eating_(t_pdata *dt);
void			_sleeping_(t_pdata *dt);
void			_thinking_(t_pdata *dt);
void			_death_(t_pdata *dt);
void			*_tasks_(void *data);
void			_init_vars_(t_philo *philo, char ** argv, int argc);
#endif