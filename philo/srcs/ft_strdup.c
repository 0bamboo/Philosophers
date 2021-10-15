/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:15:25 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/15 10:20:16 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(s);
	tmp = (char *)malloc(len + 1);
	if (!tmp)
		return (0);
	while (i < len + 1)
	{
		tmp[i] = s[i];
		i++;
	}
	return (tmp);
}
