/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:31:09 by abdait-m          #+#    #+#             */
/*   Updated: 2019/10/23 15:33:54 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char			*ptr;
	const char		*ptr2;

	ptr = (char *)dest;
	ptr2 = (const char *)src;
	if (!len)
		return (dest);
	if (ptr <= ptr2)
		return (ft_memcpy(ptr, ptr2, len));
	ptr += len;
	ptr2 += len;
	while (len--)
		*--ptr = *--ptr2;
	return (dest);
}
