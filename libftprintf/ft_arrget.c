/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:30:03 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/24 14:47:58 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned char	*ft_arrget(t_arr *arr, size_t index)
{
	if (!arr || !arr->head || arr->nbr_elem <= index)
		return (NULL);
	return (arr->head + arr->size * index);
}
