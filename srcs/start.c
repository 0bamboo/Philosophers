/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:54:13 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/06 19:09:18 by abdait-m         ###   ########.fr       */
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
	pd->limit = 0;
}

void	_init_philos_(t_philo *philo)
{
	int		i;

	philo->pdata = malloc(sizeof(t_pdata) * philo->nbr_ps);
	if (!philo->pdata)
		return ;
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nbr_ps);
	if (!philo->forks)
		return ;
	i = -1;
	while (++i < philo->nbr_ps)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		philo->pdata[i].philo = philo;
		_init_each_philo_(&philo->pdata[i], i);
	}
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
}
