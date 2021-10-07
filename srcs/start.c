/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:54:13 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/07 16:09:48 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

unsigned int	_get_time_(unsigned int start)
{
	struct timeval	time;
	unsigned int	ret;
	
	gettimeofday(&time, NULL);
	ret = (time.tv_usec / 1000) + (time.tv_sec * 1000) - start;
	return (ret);
}

void _init_each_philo_(t_pdata *pd, int i)
{
	pd->name = i;
	pd->nbr_eatings = 0;
	pd->l_fork = i;
	pd->r_fork = (i + 1) % pd->philo->nbr_ps;
	pd->limit = 0U;
}

void	_allocation_error_()
{
	puts("Allocation Error .");
	exit(0);
}

void	_allocation_(t_philo *ph)
{
	ph->pdata = malloc(sizeof(t_pdata) * ph->nbr_ps);
	if (!ph->pdata)
		_allocation_error_();
	ph->forks = malloc(sizeof(pthread_mutex_t) * ph->nbr_ps);
	if (!ph->forks)
		_allocation_error_();
}

void	*_eat_checker_(void *data)
{
	t_pdata	*dt;

	dt = (t_pdata *)data;
	while (dt->philo->end_sim)
	{
		if (dt->philo->nbr_ps == dt->philo->nbr_philos_meat)
			_print_(dt, END);
	}
	return (data);
}

void	_init_philos_(t_philo *philo)
{
	int		i;

	_allocation_(philo);
	i = -1;
	while (++i < philo->nbr_ps)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		philo->pdata[i].philo = philo;
		_init_each_philo_(&philo->pdata[i], i);
	}
	pthread_mutex_init(&philo->p_hold, NULL);
	pthread_mutex_init(&philo->print, NULL);
	pthread_create(&philo->eat_checker, NULL, &_eat_checker_, (void *)philo->pdata);
	pthread_detach(philo->eat_checker);
}


void _start_program_(t_philo *philo)
{
	int			i;
	pthread_t	th;

	_init_philos_(philo);
	i = -1;
	while (++i < philo->nbr_ps)
	{
		// puts("im in");
		pthread_create(&th, NULL, &_tasks_, (void *)&philo->pdata[i]);
		pthread_detach(th);
	}
	pthread_mutex_lock(&philo->p_hold);
	pthread_mutex_lock(&philo->p_hold);
}
