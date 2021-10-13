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
		// i think u need to add sem_wait(ph)
		if (dt->limit < _get_time_(0U))
		{
			// pthread_mutex_lock(&dt->philo->print);
			sem_wait(dt->philo->print_b);
			printf("%u\t%d\t died\n", \
				_get_time_(dt->philo->start_time), dt->name + 1);
			// pthread_mutex_unlock(&dt->philo->p_hold);
			sem_post(dt->philo->p_hold_b);
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
		// pthread_mutex_lock(&dt->philo->forks[dt->l_fork]);
		sem_wait(dt->philo->forks);
		_print_(dt, FORK);
		// pthread_mutex_lock(&dt->philo->forks[dt->r_fork]);
		sem_wait(dt->philo->forks);
		_print_(dt, EAT);
		dt->limit = _get_time_(0U) + dt->philo->t_die;
		usleep(dt->philo->t_eat * 1000);
		dt->nbr_eatings++;
		sem_post(dt->philo->forks);
		sem_post(dt->philo->forks);
		// pthread_mutex_unlock(&dt->philo->forks[dt->l_fork]);
		// pthread_mutex_unlock(&dt->philo->forks[dt->r_fork]);
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
	sem_unlink("ph");
	pd->ph = sem_open("ph", O_CREAT | O_EXCL, 700, 1);
}

int		_create_semaphore_(const char *sem_name, int val, sem_t **sem)
{
	sem_unlink(sem_name);
	*sem = sem_open(sem_name, O_CREAT, O_EXCL, 700, val);
	if (*sem == SEM_FAILED)
	{
		printf("%s semphore error\n", sem_name);
		return (1);
	}
	return (0);
}

int		_semaphores_(t_philo *phil)
{
	if (_create_semaphore("forks_b", philo->nbr_ps, &philo->forks_b) ||\
		_create_semaphore("print_b", 1, &philo->print_b) ||\
		_create_semaphore("p_hold_b", 1, &philo->p_hold_b) ||\
		_create_semaphore("eat_b", 1, &philo->eat_b))
			return (1);
	return (0);
}

int		_allocation_(t_philo *ph)
{
	ph->pdata = malloc(sizeof(t_pdata) * ph->nbr_ps);
	if (!ph->pdata)
	{
		_allocation_error_();
		return (1);
	}
	return (0);
	// allocation forks for bonus
	// ph->forks_b = malloc(sizeof(sem_t) * ph->nbr_ps);
	// if (!ph->forks_b)
	// 	_allocation_error_();
}

void	*_eat_checker_(void *data)
{
	t_pdata	*dt;

	dt = (t_pdata *)data;
	while (1)
	{
		// sem wait print
		if (dt->philo->nbr_ps == dt->philo->nbr_philos_meat)
		{
			// pthread_mutex_lock(&dt->philo->print);
			// sem_wait(dt->philo->eat_b);
			sem_wait(dt->philo->print_b);
			printf("%u\t End of simulation .\n", \
				_get_time_(dt->philo->start_time));
			// pthread_mutex_unlock(&dt->philo->p_hold);
			sem_post(dt->philo->print_b);
			break ;
		}
		usleep(50);
	}
	return (data);
}

int	_init_philos_(t_philo *philo)
{
	int		i;

	if (_allocation_(philo) || _semaphores_(phi))
		return (1);
	i = -1;
	while (++i < philo->nbr_ps)
	{
		// pthread_mutex_init(&philo->forks[i], NULL);
		_init_each_philo_(&philo->pdata[i], i);
		philo->pdata[i].philo = philo;
	}
	// pthread_mutex_init(&philo->p_hold, NULL);
	// pthread_mutex_init(&philo->print, NULL);
	pthread_create(&philo->eat_checker, NULL, \
		&_eat_checker_, (void *)philo->pdata);
	pthread_detach(philo->eat_checker);
	sem_wait(philo->sem_p_hold_p);
}

int	_start_program_(t_philo *philo)
{
	int			i;

	_init_philos_(philo);
	i = -1;
	while (++i < philo->nbr_ps)
	{
		philo->pdata[i].pid = fork();
		if (philo->pdata[i].pid == 0)
		{
			_tasks(philo);
			exit(0);
		}
		else if (philo->pdata[i].pid == -1)
			return (2);
		// pthread_create(&th, NULL, &_tasks_, (void *)&philo->pdata[i]);
		// pthread_detach(th);
		// usleep(50);
	}
	sem_wait(philo->p_hold_b);
	sem_post(philo->p_hold_b);
	return (0);
	// pthread_mutex_lock(&philo->p_hold);
	// pthread_mutex_lock(&philo->p_hold);
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