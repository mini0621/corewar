/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:02:49 by mnishimo          #+#    #+#             */
/*   Updated: 2018/11/29 10:17:11 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ps;
	unsigned char	*pd;
	size_t			i;

	i = 0;
	pd = (unsigned char *)dst;
	ps = (unsigned char *)src;
	while (i < n)
	{
		pd[i] = ps[i];
		if (ps[i] == (unsigned char)c)
			return (pd + i + 1);
		i++;
	}
	return (NULL);
}
