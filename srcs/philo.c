/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:43:57 by abdait-m          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/09/22 15:56:46 by abdait-m         ###   ########.fr       */
=======
/*   Updated: 2021/09/22 17:01:44 by abdait-m         ###   ########.fr       */
>>>>>>> 3982fad31afca81eefbc2c0013824ce36f569a37
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void* test()
{
	printf("test from thread 1\n");
	return (NULL);
}

int main()
{
	pthread_t t1;

	pthread_create(&t1, NULL, &test, NULL);
	pthread_join(t1, NULL);
	return (0);
}