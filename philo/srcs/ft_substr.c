/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:51:00 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/15 10:18:10 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		j;
	char		*sub;

	if (!s)
		return (NULL);
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	j = 0;
	while (j < len)
		sub[j++] = s[start++];
	sub[j] = '\0';
	return (sub);
}
