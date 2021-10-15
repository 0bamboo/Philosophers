/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:54:48 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/15 10:49:08 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int	if_long(long a, int sign)
{
	if (a > 0 && sign < 0)
		return (0);
	if (a < 0 && sign > 0)
		return (-1);
	return (a);
}

size_t	ft_strlen(const char *s)
{
	size_t	j;

	j = 0;
	while (*s != '\0')
	{
		j++;
		s++;
	}
	return (j);
}
