/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:15:12 by abdait-m          #+#    #+#             */
/*   Updated: 2021/10/15 10:18:06 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

static int	ft_firstchar(char const *str, char const *set)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (set[i])
	{
		if (set[i] == str[k])
		{
			i = -1;
			k++;
		}
		i++;
	}
	return (k);
}

static int	ft_lastchar(char const *str, char const *set)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (str[k])
		k++;
	k--;
	while (set[i])
	{
		if (set[i] == str[k])
		{
			k--;
			i = -1;
		}
		i++;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		l;
	char	*p;

	if (!s1)
		return (NULL);
	start = ft_firstchar(s1, set);
	if (!s1[start])
		return (ft_substr(s1, 0, 0));
	l = ft_lastchar(s1, set) - start + 1;
	p = ft_substr(s1, start, l);
	return (p);
}
