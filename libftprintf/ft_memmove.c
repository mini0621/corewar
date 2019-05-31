/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:44:41 by mnishimo          #+#    #+#             */
/*   Updated: 2018/11/29 10:18:02 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ps;
	unsigned char	*pd;
	size_t			i;

	pd = (unsigned char *)dst;
	ps = (unsigned char *)src;
	if (dst > src)
	{
		i = len - 1;
		while ((signed long)i >= 0)
		{
			pd[i] = ps[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			pd[i] = ps[i];
			i++;
		}
	}
	return (dst);
}
