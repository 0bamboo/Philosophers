/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:10:44 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/15 10:01:01 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int	_create_semaphore_(const char *sem_name, int val, sem_t **sem)
{
	sem_unlink(sem_name);
	*sem = sem_open(sem_name, O_CREAT | O_EXCL, 700, val);
	if (*sem == SEM_FAILED)
	{
		printf("Creating error of semphore %s\n", sem_name);
		return (1);
	}
	return (0);
}

int	_semaphores_(t_philo *philo)
{
	if (_create_semaphore_("forks_b", philo->nbr_ps, &philo->forks_b) || \
		_create_semaphore_("print_b", 1, &philo->print_b) || \
		_create_semaphore_("p_hold_b", 1, &philo->p_hold_b) || \
		_create_semaphore_("eat_b", 1, &philo->eat_b))
		return (1);
	return (0);
}
