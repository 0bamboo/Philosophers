/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_tasks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:13:40 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/13 20:13:40 by abdait-m         ###   ########.fr       */
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

void	_print_(t_pdata *dt, int task)
{
	// pthread_mutex_lock(&dt->philo->print);
	sem_wait(dt->philo->print_b);
	if (task == FORK)
		printf("%u\t%d\t has taken a fork\n", \
			_get_time_(dt->philo->start_time), dt->name + 1);
	else if (task == EAT)
	{
		printf("%u\t%d\t has taken a fork\n", \
			_get_time_(dt->philo->start_time), dt->name + 1);
		printf("%u\t%d\t is eating\n", \
			_get_time_(dt->philo->start_time), dt->name + 1);
	}
	else if (task == SLEEP)
		printf("%u\t%d\t is sleeping\n", \
			_get_time_(dt->philo->start_time), dt->name + 1);
	else if (task == THINK)
		printf("%u\t%d\t is thinking\n", \
			_get_time_(dt->philo->start_time), dt->name + 1);
	sem_post(dt->philo->print_b);
	// pthread_mutex_unlock(&dt->philo->print);
}

void	*_death_checker_(void *data)
{
	t_pdata	*dt;

	dt = (t_pdata *)data;
	while (1)
	{
		// sem_wait(dt->ph);
		if (dt->limit < _get_time_(0U))
		{
			sem_wait(dt->philo->print_b);
			printf("%u\t%d\t died\n", \
				_get_time_(dt->philo->start_time), dt->name + 1);
			sem_post(dt->philo->print_b);
			sem_post(dt->philo->p_hold_b);
			dt->philo->is_alive = 0;
			break ;
		}
		sem_post(dt->ph);
		usleep(100);
	}
	return (data);
}

void	*_tasks_(void *data)
{
	t_pdata	*dt;

	dt = (t_pdata *)data;
	dt->limit = _get_time_(0U) + dt->philo->t_die;
	pthread_create(&dt->philo->death_checker, NULL, &_death_checker_, data);
	pthread_detach(dt->philo->death_checker);
	while (dt->philo->is_alive)
	{
		// sem_wait(dt->philo->print_b);
		// printf("alive = |%d|\n", dt->philo->is_alive);
		// sem_post(dt->philo->print_b);
		// sem_wait(dt->ph);
		sem_wait(dt->philo->forks_b);
		_print_(dt, FORK);
		sem_wait(dt->philo->forks_b);
		_print_(dt, EAT);
		dt->limit = _get_time_(0U) + dt->philo->t_die;
		usleep(dt->philo->t_eat * 1000);
		dt->nbr_eatings++;
		// sem_post(dt->ph);
		sem_post(dt->philo->forks_b);
		sem_post(dt->philo->forks_b);
		_print_(dt, SLEEP);
		usleep(dt->philo->t_sleep * 1000);
		_print_(dt, THINK);
		if (dt->philo->nbr_peat && dt->nbr_eatings == dt->philo->nbr_peat)
			dt->philo->nbr_philos_meat++;
	}
	return (data);
}