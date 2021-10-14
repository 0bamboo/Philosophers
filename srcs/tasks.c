/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:59:19 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/07 14:59:19 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

unsigned int _get_time_(unsigned int start)
{
	struct timeval time;
	unsigned int ret;

	gettimeofday(&time, NULL);
	ret = (time.tv_usec / 1000) + (time.tv_sec * 1000) - start;
	return (ret);
}

void _print_(t_pdata *dt, int task)
{
	pthread_mutex_lock(&dt->philo->print);
	if (task == FORK)
		printf("%u\t%d\t has taken a fork\n",
			   _get_time_(dt->philo->start_time), dt->name + 1);
	else if (task == EAT)
	{
		printf("%u\t%d\t has taken a fork\n",
			   _get_time_(dt->philo->start_time), dt->name + 1);
		pthread_mutex_lock(&dt->ph_mutex);
		printf("%u\t%d\t is eating\n",
			   _get_time_(dt->philo->start_time), dt->name + 1);
	}
	else if (task == SLEEP)
		printf("%u\t%d\t is sleeping\n",
			   _get_time_(dt->philo->start_time), dt->name + 1);
	else if (task == THINK)
		printf("%u\t%d\t is thinking\n",
			   _get_time_(dt->philo->start_time), dt->name + 1);
	pthread_mutex_unlock(&dt->philo->print);
}

void *_death_checker_(void *data)
{
	t_pdata *dt;

	dt = (t_pdata *)data;
	while (1)
	{
		pthread_mutex_lock(&dt->ph_mutex);
		if (dt->limit < _get_time_(0U))
		{
			pthread_mutex_lock(&dt->philo->print);
			printf("%u\t%d\t died\n",
				   _get_time_(dt->philo->start_time), dt->name + 1);
			pthread_mutex_unlock(&dt->philo->p_hold);
			dt->philo->is_alive = 0;
			break;
		}
		pthread_mutex_unlock(&dt->ph_mutex);
		usleep(50);
	}
	return (data);
}

void *_tasks_(void *data)
{
	t_pdata *dt;

	dt = (t_pdata *)data;
	dt->limit = _get_time_(0U) + dt->philo->t_die;
	pthread_create(&dt->philo->death_checker, NULL, &_death_checker_, data);
	pthread_detach(dt->philo->death_checker);
	while (dt->philo->is_alive)
	{
		pthread_mutex_lock(&dt->philo->forks[dt->l_fork]);
		_print_(dt, FORK);
		pthread_mutex_lock(&dt->philo->forks[dt->r_fork]);
		_print_(dt, EAT);
		dt->limit = _get_time_(0U) + dt->philo->t_die;
		usleep(dt->philo->t_eat * 1000);
		dt->nbr_eatings++;
		pthread_mutex_unlock(&dt->ph_mutex);
		pthread_mutex_unlock(&dt->philo->forks[dt->l_fork]);
		pthread_mutex_unlock(&dt->philo->forks[dt->r_fork]);
		_print_(dt, SLEEP);
		usleep(dt->philo->t_sleep * 1000);
		_print_(dt, THINK);
		if (dt->philo->nbr_peat && dt->nbr_eatings == dt->philo->nbr_peat)
			dt->philo->nbr_philos_meat++;
	}
	return (NULL);
}
