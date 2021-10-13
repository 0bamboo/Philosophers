/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:43:57 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/08 17:44:03 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
