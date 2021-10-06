/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:54:13 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/06 18:26:21 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void _init_each_philo_(t_pdata *pd, int i)
{
	pd->name = i;
	pd->nbr_eatings = 0;
	pd->l_fork = i;
	pd->r_fork = (i + 1) % pd->philo->nbr_ps;
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

unsigned int	_get_time_(unsigned int start)
{
	struct timeval time;
	unsigned int	ret;
	
	gettimeofday(&time, NULL);
	ret = (time.tv_usec / 1000) + (time.tv_sec * 1000) - start;
	return (ret);
}

void	_eating_(t_pdata *dt)
{
	// you need infinite loop here
	pthread_mutex_lock(&dt->philo->forks[dt->l_fork]);
	//print the time each time 
	printf("%d\t has taken a fork", dt->name);
	pthread_mutex_lock(&dt->philo->forks[dt->r_fork]);
	printf("%d\t has taken a fork", dt->name);
	
	printf("%d\t is eating", dt->name);
	usleep(dt->philo->t_eat * 1000);
	dt->nbr_eatings++;
	pthread_mutex_unlock(&dt->philo->forks[dt->l_fork]);
	pthread_mutex_unlock(&dt->philo->forks[dt->r_fork]);
}

void	_sleeping_(t_pdata *dt)
{
	printf("%d is sleeping\n", dt->name);
	usleep(dt->philo->t_sleep * 1000);
}

void	_thinking_(t_pdata *dt)
{
	printf("%d is thinking\n", dt->name);
}

void	_death_(t_pdata *dt)
{
	dt->name = 3;
}

void	*_tasks_(void *data)
{
	t_pdata *dt;
	
	dt = (t_pdata *)data;
	_eating_(dt);
	_sleeping_(dt);
	_thinking_(dt);
	_death_(dt);
	return NULL;
}

void _start_program_(t_philo *philo)
{
	int		i;
	pthread_t  th;

	_init_philos_(philo);
	i = -1;
	while (++i < philo->nbr_ps)
	{
		pthread_create(&th, NULL, &_tasks_, (void *)&philo->pdata[i]);
		pthread_detach(th);
	}
}
