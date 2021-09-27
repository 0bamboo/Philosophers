/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:52:11 by abdait-m          #+#    #+#             */
/*   Updated: 2021/07/01 13:17:21 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_nbr(long n)
{
	int		size;

	size = 0;
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ptr;
	int		i;
	long	a;

	a = n;
	if (a == 0)
		return (ft_strdup("0"));
	len = ft_len_nbr(a);
	i = len - 1;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	if (a < 0)
	{
		ptr[0] = '-';
		a *= -1;
	}
	while (a)
	{
		ptr[i--] = (a % 10) + '0';
		a /= 10;
	}
	ptr[len] = '\0';
	return (ptr);
}
