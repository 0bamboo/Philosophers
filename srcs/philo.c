/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:43:57 by abdait-m          #+#    #+#             */
/*   Updated: 2021/09/29 14:54:29 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

// ARGS :
// number of philosophers
// time to die
// time to eat
// time to sleep 
// number of times each philo must eat

int main(int argc, char **argv)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	_init_vars_(philo, argv, argc);
	_check_options_(philo);
	if (philo->error)
		_error_();
	_start_program_(philo);
}