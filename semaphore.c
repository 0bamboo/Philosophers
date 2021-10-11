# include "header/philosophers.h"
//--------------- tasks file ---------------------

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
	pthread_mutex_lock(&dt->philo->print);
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
	pthread_mutex_unlock(&dt->philo->print);
}

void	*_death_checker_(void *data)
{
	t_pdata	*dt;

	dt = (t_pdata *)data;
	while (1)
	{
		if (dt->limit < _get_time_(0U))
		{
			pthread_mutex_lock(&dt->philo->print);
			printf("%u\t%d\t died\n", \
				_get_time_(dt->philo->start_time), dt->name + 1);
			pthread_mutex_unlock(&dt->philo->p_hold);
			dt->philo->is_alive = 0;
			break ;
		}
		usleep(50);
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
		pthread_mutex_lock(&dt->philo->forks[dt->l_fork]);
		_print_(dt, FORK);
		pthread_mutex_lock(&dt->philo->forks[dt->r_fork]);
		_print_(dt, EAT);
		dt->limit = _get_time_(0U) + dt->philo->t_die;
		usleep(dt->philo->t_eat * 1000);
		dt->nbr_eatings++;
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

//------------------------------------------------
//----------------- start file -------------------
void	_init_each_philo_(t_pdata *pd, int i)
{
	pd->name = i;
	pd->nbr_eatings = 0;
	pd->l_fork = i;
	pd->r_fork = (i + 1) % pd->philo->nbr_ps;
	pd->limit = 0U;
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
	pthread_create(&philo->eat_checker, NULL, \
		&_eat_checker_, (void *)philo->pdata);
	pthread_detach(philo->eat_checker);
}

void	_start_program_(t_philo *philo)
{
	int			i;
	pthread_t	th;

	_init_philos_(philo);
	i = -1;
	while (++i < philo->nbr_ps)
	{
		pthread_create(&th, NULL, &_tasks_, (void *)&philo->pdata[i]);
		pthread_detach(th);
		usleep(50);
	}
	pthread_mutex_lock(&philo->p_hold);
	pthread_mutex_lock(&philo->p_hold);
}
//-------------------------------

int	main(int argc, char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	_init_vars_(philo, argv, argc);
	_check_options_(philo);
	if (philo->error)
		_error_();
	_start_program_(philo);
	_clean_(philo);
}
