/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:21:14 by abdait-m          #+#    #+#             */
/*   Updated: 2019/10/23 17:14:02 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t		pos;
	size_t		i;
	char		*s;

	s = (char *)str;
	if (!*to_find)
		return (s);
	pos = 0;
	while (s[pos] != '\0' && pos < len)
	{
		if (s[pos] == to_find[0])
		{
			i = 1;
			while (to_find[i] != '\0' && (pos + i) < len)
			{
				if (to_find[i] != s[pos + i])
					break ;
				++i;
			}
			if (to_find[i] == '\0')
				return (s + pos);
		}
		++pos;
	}
	return (0);
}
