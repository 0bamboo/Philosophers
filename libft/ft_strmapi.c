/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 17:22:41 by abdait-m          #+#    #+#             */
/*   Updated: 2021/07/01 12:22:11 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapi;
	unsigned int	i;
	unsigned int	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	mapi = (char *)malloc(sizeof(char) * (len + 1));
	if (!mapi)
		return (NULL);
	while (s[i] != '\0')
	{
		mapi[i] = (*f)(i, s[i]);
		i++;
	}
	mapi[i] = '\0';
	return (mapi);
}
