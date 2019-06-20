/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:54:14 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/20 20:35:01 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	*ft_memjoin(void *s1, void *s2, size_t len_s1, size_t len_s2)
{
	char *ret;

	if (s1 == NULL)
	{
		if (!(ret = ft_memalloc(len_s2)))
			return (NULL);
		ft_memcpy(ret, s2, len_s2);
	}
	else if (s2 == NULL)
	{
		if (!(ret = ft_memalloc(len_s1)))
			return (NULL);
		ft_memcpy(ret, s1, len_s1);
	}
	else
	{
		if (!(ret = ft_memalloc(len_s1 + len_s2)))
			return (NULL);
		ft_memcpy(ret, s1, len_s1);
		ft_memcpy(ret + len_s1, s2, len_s2);
	}
	return (ret);
}
