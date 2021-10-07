
#include "../header/philosophers.h"

void	_eating_(t_pdata *dt)
{
	//print the time each time 
	pthread_mutex_lock(&dt->philo->forks[dt->l_fork]);
	printf("%d\t has taken a fork\n", dt->name);
	pthread_mutex_lock(&dt->philo->forks[dt->r_fork]);
	printf("%d\t has taken a fork\n", dt->name);
	printf("%d\t is eating\n", dt->name);
	dt->limit = _get_time_(0) + dt->philo->t_die;
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

void	*_death_(void *data)
{
	t_pdata *dt;
	
	dt = (t_pdata *)data;
	while(1)
	{
		// printf("dt->limit = |%u|===|%u|\n", dt->limit, _get_time_(dt->philo->start_time));
		if (dt->limit < _get_time_(dt->philo->start_time))
		{
			printf("%d\t died\n", dt->name);
			dt->philo->is_alive = 0;
			break;
		}
	}
	return (NULL);
}

void	*_tasks_(void *data)
{
	t_pdata		*dt;
	pthread_t	th;
	
	dt = (t_pdata *)data;
	dt->limit = _get_time_(0) + dt->philo->t_die;
	// printf("dtlimit = -----|%u|-----\n", dt->philo->start_time);
	pthread_create(&th, NULL, &_death_, data);
	pthread_detach(th);
	// printf("---{%d}\n", dt->philo->is_alive);
	while (dt->philo->is_alive)
	{
		_eating_(dt);
		_sleeping_(dt);
		_thinking_(dt);
		// _death_(dt);
	}
	return (NULL);
}