/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:54:13 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/08 17:40:42 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	_init_each_philo_(t_pdata *pd, int i)
{
	pd->name = i;
	pd->nbr_eatings = 0;
	pd->l_fork = i;
	pd->r_fork = (i + 1) % pd->philo->nbr_ps;
	pd->limit = 0U;
}

int	_allocation_(t_philo *ph)
{
	ph->pdata = malloc(sizeof(t_pdata) * ph->nbr_ps);
	if (!ph->pdata)
		return (_allocation_error_());
	ph->forks = malloc(sizeof(pthread_mutex_t) * ph->nbr_ps);
	if (!ph->forks)
		return (_allocation_error_());
	return (0);
}

void	*_eat_checker_(void *data)
{
	t_pdata	*dt;

	dt = (t_pdata *)data;
	while (1)
	{
		if (dt->philo->nbr_ps == dt->philo->nbr_philos_meat)
		{
			pthread_mutex_lock(&dt->philo->print);
			printf("%u\t End of simulation .\n", \
				_get_time_(dt->philo->start_time));
			pthread_mutex_unlock(&dt->philo->p_hold);
			break ;
		}
		usleep(50);
	}
	return (data);
}

int	_init_philos_(t_philo *philo)
{
	int		i;

	if (_allocation_(philo))
		return (1);
	i = -1;
	while (++i < philo->nbr_ps)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		philo->pdata[i].philo = philo;
		_init_each_philo_(&philo->pdata[i], i);
	}
	pthread_mutex_init(&philo->p_hold, NULL);
	pthread_mutex_init(&philo->print, NULL);
	pthread_create(&philo->eat_checker, NULL, \
		&_eat_checker_, (void *)philo->pdata);
	pthread_detach(philo->eat_checker);
	return (0);
}

int	_start_program_(t_philo *philo)
{
	int			i;
	pthread_t	th;

	if (_init_philos_(philo))
		return (1);
	i = -1;
	while (++i < philo->nbr_ps)
	{
		pthread_create(&th, NULL, &_tasks_, (void *)&philo->pdata[i]);
		pthread_detach(th);
		usleep(50);
	}
	pthread_mutex_lock(&philo->p_hold);
	pthread_mutex_lock(&philo->p_hold);
	return (0);
}
