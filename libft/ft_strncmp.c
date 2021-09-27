/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:36:49 by abdait-m          #+#    #+#             */
/*   Updated: 2021/06/30 14:56:37 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*t;

	p = (unsigned char *)s1;
	t = (unsigned char *)s2;
	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (p[i] != '\0' && t[i] != '\0' && i < n)
	{
		if (p[i] != t[i])
			return (p[i] - t[i]);
		i++;
	}
	if (i != n)
		return (p[i] - t[i]);
	return (0);
}
