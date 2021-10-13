#include "../header/philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	_init_vars_(philo, argv, argc);
	_check_options_(philo);
	if (philo->error)
		return (_error_());
	if (_start_program_(philo))
		return (1);
	_clean_(philo);
	return (0);
}
