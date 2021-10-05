/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:50:56 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/05 17:21:59 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	_init_vars_(t_philo *philo, char ** argv, int argc)
{
	int	i;

	i = 0;
	while (i < 5)
		philo->int_options[i++] = 0;
	philo->nbr_ps = 0;
	philo->t_eat = 0;
	philo->t_die = 0;
	philo->t_sleep = 0;
	philo->nbr_peat = 0;
	philo->error = 0;
	philo->options = argv;
	philo->nbr_opt = argc - 1;
}

void _error_()
{
	puts("\033[31m Error.\033[0m");
	exit(0);
}