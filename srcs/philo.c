/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:43:57 by abdait-m          #+#    #+#             */
/*   Updated: 2021/09/22 17:01:44 by abdait-m         ###   ########.fr       */
/* ************************************************************************** */

#include "../header/philosophers.h"

// ARGS :
// number of philosophers
// time to die
// time to eat
// time to sleep 
// number of times each philo must eat
void	_init_vars_(t_philo *philo)
{
	philo->options = NULL;
	philo->nbr_ps = 0;
	philo->t_eat = 0;
	philo->t_die = 0;
	philo->t_sleep = 0;
	philo->nbr_peat = 0;
	philo->error = 0;
}

void	_check_options_(t_philo *philo, int argc)
{
	if (argc != 5 || argc != 6)
	{
		philo->error = 1;
		return ;
	}
}

void _error_()
{
	puts("Options error .\n");
	exit(0);
}

void _start_program_()

int main(int argc, char **argv)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	_init_vars_(philo);
	_check_options_(philo, argc);
	if (philo->error)
		_error_();
	_start_program_(philo);
	philo->options = argv;
	argc += 2;
	printf("argv = %s", philo->options[1]);
}