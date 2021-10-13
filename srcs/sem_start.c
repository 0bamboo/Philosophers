/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:13:37 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/13 20:13:37 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int		_create_semaphore_(const char *sem_name, int val, sem_t **sem)
{
	sem_unlink(sem_name);
	*sem = sem_open(sem_name, O_CREAT, O_EXCL, 700, val);
	if (*sem == SEM_FAILED)
	{
		printf("%s semphore error\n", sem_name);
		return (1);
	}
	return (0);
}

int		_semaphores_(t_philo *philo)
{
	if (_create_semaphore_("forks_b", philo->nbr_ps, &philo->forks_b) ||\
		_create_semaphore_("print_b", 1, &philo->print_b) ||\
		_create_semaphore_("p_hold_b", 1, &philo->p_hold_b) ||\
		_create_semaphore_("eat_b", 1, &philo->eat_b))
			return (1);
	return (0);
}

int	_allocation_error_(void)
{
	puts("\033[31m Allocation Error .\033[0m");
	return (1);
}

int		_allocation_(t_philo *ph)
{
	ph->pdata = malloc(sizeof(t_pdata) * ph->nbr_ps);
	if (!ph->pdata)
		return (_allocation_error_());
	return (0);
}

void	*_eat_checker_(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	while (1)
	{
		sem_wait(ph->eat_b);
		if (ph->nbr_ps == ph->nbr_philos_meat)
		{
			sem_wait(ph->print_b);
			printf("%u\t End of simulation .\n", \
				_get_time_(ph->start_time));
			sem_post(ph->print_b);
			return (data);
		}
		usleep(50);
	}
	return (data);
}

int	_init_philos_(t_philo *philo)
{
	int		i;

	if (_allocation_(philo) || _semaphores_(philo))
		return (1);
	i = -1;
	while (++i < philo->nbr_ps)
	{
		_init_each_philo_sem_(&philo->pdata[i], i, philo->nbr_ps);
		philo->pdata[i].philo = philo;
	}
	// pthread_create(&philo->eat_checker, NULL, \
	// 	&_eat_checker_, (void *)philo);
	// pthread_detach(philo->eat_checker);
	sem_wait(philo->p_hold_b);
	return (0);
}

int	_start_program_(t_philo *philo)
{
	int			i;

	if (_init_philos_(philo))
		return (1);
	i = -1;
	while (++i < philo->nbr_ps)
	{
		philo->pdata[i].pid = fork();
		if (philo->pdata[i].pid > 0)
		{
			_tasks_(&philo->pdata[i]);
			exit(0);
		}
		else if (philo->pdata[i].pid == -1)
			return (2);
	}
	sem_wait(philo->p_hold_b);
	sem_post(philo->p_hold_b);
	return (0);
}