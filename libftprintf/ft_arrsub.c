/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:19:29 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/24 16:44:43 by mnishimo         ###   ########.fr       */
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
		arr->last--;
		return ;
	}
	ptr = arr->head + arr->size * (index + 1);
	ft_memcpy(arr->head + arr->size * index, ptr,
			arr->head + arr->size * arr->last - ptr);
	arr->last--;
}
