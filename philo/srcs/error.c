/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:50:56 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/14 17:07:57 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	_init_vars_(t_philo *philo, char **argv, int argc)
{
	int	i;

	i = 0;
	philo->start_time = _get_time_(0U);
	while (i < 5)
		philo->int_options[i++] = 0;
	philo->nbr_ps = 0;
	philo->t_eat = 0;
	philo->t_die = 0;
	philo->t_sleep = 0;
	philo->nbr_peat = 0;
	philo->error = 0;
	philo->is_alive = 1;
	philo->nbr_philos_meat = 0;
	philo->end_sim = 1;
	philo->options = argv;
	philo->nbr_opt = argc - 1;
}

int	_error_(void)
{
	printf("\033[31mError.\033[0m\n");
	printf("\033[33mUSAGE : \n");
	printf(" [ARG 1] : Number of philosophers.\n");
	printf(" [ARG 2] : Time to die .\n");
	printf(" [ARG 3] : Time to eat .\n");
	printf(" [ARG 4] : Time to sleep .\n");
	printf(" [ARG 5][optional] : Number of times\
	each philosopher must eat .\033[0m\n");
	return (1);
}

int	_allocation_error_(void)
{
	printf("\033[31m Allocation Error .\033[0m\n");
	return (1);
}

void	_clean_(t_philo *ph)
{
	while (ph->nbr_ps--)
		pthread_mutex_destroy(&ph->forks[ph->nbr_ps]);
	free(ph->forks);
	free(ph->pdata);
	pthread_mutex_destroy(&ph->print);
	pthread_mutex_destroy(&ph->p_hold);
	free(ph);
}
