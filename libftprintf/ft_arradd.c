/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:18:46 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/24 15:27:42 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_arradd(t_arr *arr, void *new, size_t size, int index)
{
	size_t	i;

	i = (index < 0) ? arr->last + 1 : (size_t)index;
	if (arr->size != size || arr->nbr_elem <= i)
		return (-1);
	ft_memcpy(arr->head + size * i, new, size);
	if (arr->last < (int)i)
		arr->last = i;
	return (1);
}
