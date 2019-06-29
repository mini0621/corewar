/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrresize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:32:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/27 14:02:33 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_arrresize(t_arr *arr, size_t nbr_elem)
{
	unsigned char	*new;

	if (!arr || !arr->head)
		return (-1);
	if (!(new = (unsigned char *)malloc(arr->size * nbr_elem)))
		return (-1);
	ft_bzero(new, arr->size * nbr_elem);
	if (arr->nbr_elem > nbr_elem)
		ft_memcpy(new, arr->head, arr->size * nbr_elem);
	else
		ft_memcpy(new, arr->head, arr->size * arr->nbr_elem);
	free(arr->head);
	arr->head = new;
	arr->nbr_elem = nbr_elem;
	return (1);
}
