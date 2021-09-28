/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:43:57 by abdait-m          #+#    #+#             */
/*   Updated: 2021/09/28 17:57:05 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

// ARGS :
// number of philosophers
// time to die
// time to eat
// time to sleep 
// number of times each philo must eat

void	_init_vars_(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < 5)
		philo->int_options[i++] = 0;
	philo->options = NULL;
	philo->nbr_ps = 0;
	philo->t_eat = 0;
	philo->t_die = 0;
	philo->t_sleep = 0;
	philo->nbr_peat = 0;
	philo->error = 0;
	philo->nbr_z = 0;
}

void _error_()
{
	puts("\033[31m Error.\033[0m\n");
	exit(0);
}

size_t		_nbrlen_(int nbr)
{
	size_t	len;

	len = 0;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

int		_count_zeros_(char *str)
{
	int	i;

	i = -1;
	if ((str[0] == '+' || str[0] == '-') && str[1])
		i = 0;
	while (str[++i] == '0');
	return (i);
}

int		_atoi_kai_(t_philo *philo, char *str)
{
	int		i;
	long	a;
	int		sign;
	size_t	slen;

	a = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		philo->error = 1;
		return (0);
	}
	slen = ft_strlen(str) - _count_zeros_(str);
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = (a * 10) + str[i] - 48;
		i++;
	}
	if (a > MAX_INT || slen != _nbrlen_(a))
		philo->error = 1;
	a = a * sign;
	return (if_long(a, sign));
}

void	_set_vars_(t_philo *philo)
{
	philo->nbr_ps = philo->int_options[0];
	philo->t_die = philo->int_options[1];
	philo->t_eat = philo->int_options[2];
	philo->t_sleep = philo->int_options[3];
	if (philo->nbr_opt == 5)
		philo->nbr_peat = philo->int_options[4];
}

void	_check_options_(t_philo *philo)
{
	int	i;
	
	if (philo->nbr_opt != 4 && philo->nbr_opt != 5)
	{
		philo->error = 1;
		return ;
	}
	i = 0;
	while (philo->options[++i])
	{
		philo->int_options[i - 1] = _atoi_kai_(philo, ft_strtrim(philo->options[i], " \n\t\b\v\f\r"));
		if (philo->error)
			_error_();
	}
	if (philo->int_options[0] > 200 || philo->int_options[1] < 60
		|| philo->int_options[2] < 60 || philo->int_options[3] < 60)
		_error_();
	_set_vars_(philo);
}


void _start_program_(t_philo *philo)
{
	philo->nbr_peat += 2;
}

int main(int argc, char **argv)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	_init_vars_(philo);
	philo->options = argv;
	philo->nbr_opt = argc - 1;
	_check_options_(philo);
	if (philo->error)
		_error_();
	_start_program_(philo);
	argc += 2;
}