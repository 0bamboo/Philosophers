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

void _print_(t_pdata *dt, int task)
{
	// pthread_mutex_lock(&dt->philo->print);
	// if (task == EAT)
	// 	_eating_(dt);
	if (task == DEATH)
		_death_of_ph_(dt);
	else if (task == END)
		_end_of_simulation_(dt);
	// else if (task == SLEEP)
	// 	_sleeping_(dt);
	// else if (task == THINK)
	// 	_thinking_(dt);
	// pthread_mutex_unlock(&dt->philo->print);
}

void _eating_(t_pdata *dt)
{
			pthread_mutex_lock(&dt->philo->forks[dt->l_fork]);

		pthread_mutex_lock(&dt->philo->print);
		printf("%u\t%d\t has taken a fork\n", _get_time_(dt->philo->start_time), dt->name + 1);
		pthread_mutex_unlock(&dt->philo->print);

		pthread_mutex_lock(&dt->philo->forks[dt->r_fork]);

		pthread_mutex_lock(&dt->philo->print);
		printf("%u\t%d\t has taken a fork\n", _get_time_(dt->philo->start_time), dt->name + 1);
		printf("%u\t%d\t is eating\n", _get_time_(dt->philo->start_time), dt->name + 1);
		pthread_mutex_unlock(&dt->philo->print);

		dt->limit = _get_time_(0U) + dt->philo->t_die;
		usleep(dt->philo->t_eat * 1000);
		dt->nbr_eatings++;
		pthread_mutex_unlock(&dt->philo->forks[dt->l_fork]);
		pthread_mutex_unlock(&dt->philo->forks[dt->r_fork]);
}

// void _sleeping_(t_pdata *dt)
// {
// }

// void _thinking_(t_pdata *dt)
// {
// }

void _death_of_ph_(t_pdata *dt)
{
	pthread_mutex_lock(&dt->philo->print);
	printf("%u\t%d\t died\n", _get_time_(dt->philo->start_time), dt->name + 1);
	pthread_mutex_unlock(&dt->philo->print);
	dt->philo->is_alive = 0;
	pthread_mutex_unlock(&dt->philo->p_hold);
	pthread_mutex_lock(&dt->philo->print);
}

void _end_of_simulation_(t_pdata *dt)
{
	pthread_mutex_lock(&dt->philo->print);
	printf("%u\t End of simulation .\n", _get_time_(dt->philo->start_time));
	pthread_mutex_unlock(&dt->philo->print);
	pthread_mutex_unlock(&dt->philo->p_hold);
	pthread_mutex_lock(&dt->philo->print);
}

void *_death_checker_(void *data)
{
	t_pdata *dt;

	dt = (t_pdata *)data;
	while (1)
	{
		if (dt->limit < _get_time_(0U))
		{
			_print_(dt, DEATH);
			break;
		}
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
		// eat
		pthread_mutex_lock(&dt->philo->forks[dt->l_fork]);

		pthread_mutex_lock(&dt->philo->print);
		printf("%u\t%d\t has taken a fork\n", _get_time_(dt->philo->start_time), dt->name + 1);
		pthread_mutex_unlock(&dt->philo->print);

		pthread_mutex_lock(&dt->philo->forks[dt->r_fork]);

		pthread_mutex_lock(&dt->philo->print);
		printf("%u\t%d\t has taken a fork\n", _get_time_(dt->philo->start_time), dt->name + 1);
		printf("%u\t%d\t is eating\n", _get_time_(dt->philo->start_time), dt->name + 1);
		pthread_mutex_unlock(&dt->philo->print);

		dt->limit = _get_time_(0U) + dt->philo->t_die;
		usleep(dt->philo->t_eat * 1000);
		dt->nbr_eatings++;
		pthread_mutex_unlock(&dt->philo->forks[dt->l_fork]);
		pthread_mutex_unlock(&dt->philo->forks[dt->r_fork]);
		// _print_(dt, EAT);
		
		pthread_mutex_lock(&dt->philo->print);
		printf("%u\t%d\t is sleeping\n", _get_time_(dt->philo->start_time), dt->name + 1);
		pthread_mutex_unlock(&dt->philo->print);
		
		usleep(dt->philo->t_sleep * 1000);

		pthread_mutex_lock(&dt->philo->print);
		printf("%u\t%d\t is thinking\n", _get_time_(dt->philo->start_time), dt->name + 1);
		pthread_mutex_unlock(&dt->philo->print);

		if (dt->philo->nbr_peat && dt->nbr_eatings == dt->philo->nbr_peat)
			dt->philo->nbr_philos_meat++;
	}
	return (NULL);
}