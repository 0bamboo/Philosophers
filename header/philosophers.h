/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:21:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/09/29 14:54:47 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILOSOPHERS_H

#define _PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include "../libft/libft.h"

# define MAX_INT 2147483647

typedef struct s_philo
{
	char		**options;
	int			int_options[5];
	int			nbr_ps;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			nbr_peat;
	int			error;
	int			nbr_opt;
	int			nbr_z;
}				t_philo;

void	_check_options_(t_philo *philo);
void	_start_program_(t_philo *philo);
void	_error_();
void	_init_vars_(t_philo *philo, char ** argv, int argc);
#endif