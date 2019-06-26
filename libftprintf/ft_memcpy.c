/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 16:28:33 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/26 16:22:42 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ps;
	unsigned char	*pd;
	size_t			i;

	i = 0;
	if (!dst || !src || !n)
		return (dst);
	pd = (unsigned char *)dst;
	ps = (unsigned char *)src;
	while (i < n)
	{
		pd[i] = ps[i];
		i++;
	}
	return (dst);
}
