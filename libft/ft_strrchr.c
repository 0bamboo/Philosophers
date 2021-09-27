/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:25:52 by abdait-m          #+#    #+#             */
/*   Updated: 2019/10/23 16:15:15 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	size_t	i;

	p = (char *)s;
	i = 0;
	while (p[i])
		i++;
	if ((unsigned char)c == '\0')
		return (p + i);
	while (i)
	{
		if (p[i] == (unsigned char)c)
			return (p + i);
		i--;
	}
	if ((unsigned char)c == p[0])
		return (p);
	return (0);
}
