/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_all_ws.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 14:25:20 by abdait-m          #+#    #+#             */
/*   Updated: 2021/07/01 21:59:15 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_is_white_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	_count_words(char const *s)
{
	int	count;

	count = 0;
	while (*s && _is_white_space(*s))
		s++;
	while (*s)
	{
		if ((_is_white_space(*s) && !(_is_white_space(*(s + 1))))
			|| *(s + 1) == '\0')
			count++;
		s++;
	}
	return (count);
}

static int	_len_words(char const *s)
{
	int	k;

	k = 0;
	while (s[k] && !(_is_white_space(s[k])))
		k++;
	return (k);
}

char	**_split_all(char const *s)
{
	char		**p;
	t_norm		n;

	if (!s)
		return (NULL);
	n.size = _count_words(s);
	p = (char **)malloc(sizeof(char *) * (n.size + 1));
	if (!p)
		return (NULL);
	n.i = 0;
	while (n.i < n.size)
	{
		while (*s && _is_white_space(*s))
			s++;
		p[n.i] = (char *)malloc(sizeof(char) * (_len_words(s) + 1));
		if (!p[n.i])
			return (ft_free(p, n.size));
		n.j = 0;
		while (*s && !(_is_white_space(*s)))
			p[n.i][n.j++] = *s++;
		p[n.i++][n.j] = '\0';
	}
	p[n.i] = NULL;
	return (p);
}
