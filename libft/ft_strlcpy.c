/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:56:45 by abdait-m          #+#    #+#             */
/*   Updated: 2019/10/23 15:34:52 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		len;
	size_t		max;
	char		*d;

	i = 0;
	if (!src)
		return (0);
	d = dst;
	max = size - 1;
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (src[i] != '\0' && max > 0)
	{
		d[i] = src[i];
		i++;
		max--;
	}
	d[i] = '\0';
	return (len);
}
