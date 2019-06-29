/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:19:29 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/27 14:12:42 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_arrsub(t_arr *arr, size_t index)
{
	unsigned char	*ptr;

	if (!arr || arr->nbr_elem <= index || arr->last < (int)index)
		return ;
	if (arr->last == (int)index)
	{
		ft_bzero(arr->head + arr->size * index, arr->size);
		arr->last -= 1;
		return ;
	}
	ptr = arr->head + arr->size * (index + 1);
	ft_memcpy(arr->head + arr->size * index, ptr,
			arr->head + arr->size * (arr->last + 1) - ptr);
	ft_bzero(arr->head + arr->size * arr->last, arr->size);
	arr->last -= 1;
}
