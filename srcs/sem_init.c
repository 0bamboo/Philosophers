/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:13:44 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/13 20:13:44 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	_clean_(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < (unsigned int)philo->nbr_ps)
	{
		kill(philo->pdata[i].pid, SIGTERM);
		i++;
	}
	sem_unlink("forks_b");
	sem_unlink("p_hold_b");
	sem_unlink("print_b");
	free(philo->pdata);
	free(philo);
}

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
	printf("\033[31m Error.\033[0m\n");
	printf("\033[33m [ARG 1] : Number of philosophers. ]\n");
	printf(" [ARG 2] : Time to die \n");
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

void	_init_each_philo_sem_(t_pdata *pd, int i, int nbr_philos)
{
	pd->name = i;
	pd->nbr_eatings = 0;
	pd->l_fork = i;
	pd->r_fork = (i + 1) % nbr_philos;
	pd->limit = 0U;
	sem_unlink("ph");
	pd->ph = sem_open("ph", O_CREAT | O_EXCL, 700, 1);
	if (pd->ph == SEM_FAILED)
	{
		puts("Creating error");
		exit(0);
	}
}
