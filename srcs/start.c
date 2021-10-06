/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:54:13 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/06 15:08:09 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void _init_each_philo_(t_pdata *pdata, int i)
{
	pdata->name = i;
	pdata->nbr_eatings = 0;
	pdata->l_fork = i;
	pdata->right = (i + 1) % pdata->philo->nbr_ps;
}

void	_init_philos_(t_philo *philo)
{
	pthread_t philo;
	int		i:

	i = -1;
	philo->pdata = malloc(sizeof(t_pdata) * philo->nbr_ps);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nbr_ps);
	while (++i < philo->nbr_ps)
	{
		pthread_mutex_init(&philo->forks[i]);
		philo->pdata[i].philo = philo;
		_init_each_philo_(&philo->pdata[i]);
	}
}

unsigned int	_get_time_(unsigned int start)
{
	struct timeval time;
	unsigned int	ret;
	
	gettimeofday(&time, NULL);
	ret = (time.tv_usec / 1000) + (time.tv_sec * 1000) - start;
	return (ret);
}

void	*_tasks_(void *data)
{
	t_pdata *dt;
	dt = (t_pdata *)data;
	pthread_mutex_lock(&dt->philo->forks[dt->l_fork]);
	//print the time each time 
	printf("%d\thas taken a fork", dt->name);
	pthread_mutex_lock(&dt->philo->forks[dt->r_fork]);
	printf("%d\thas taken a fork", dt->name);
	printf("%d\t is eating", dt->name);
	usleep(dt->philo->t_eat * 1000);
	pthread_mutex_unlock(&dt->philo->forks[dt->l_fork]);
	pthread_mutex_unlock(&dt->philo->forks[dt->r_fork]);
	
	
}

void _start_program_(t_philo *philo)
{
	int		i;
	pthread_t  th;

	i = -1;
	_init_philos_(philo);
	while (++i < philo->nbr_ps)
	{
		pthread_create(&th, NULL, &_tasks_, (void *)philo->pdata[i]);
		pthread_detach(th);
	}
	philo->error = 0;
}
