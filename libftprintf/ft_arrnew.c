/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:07:26 by mnishimo          #+#    #+#             */
/*   Updated: 2019/07/01 12:13:44 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_arr	*ft_arrnew(size_t size, size_t nbr_elem)
{
	t_arr	*ret;

	if (!(ret = (t_arr *)malloc(sizeof(t_arr))))
		return (NULL);
	ret->nbr_elem = nbr_elem;
	ret->size = size;
	ret->last = -1;
	if (!(ret->head = (unsigned char *)malloc(size * nbr_elem)))
	{
		free(ret);
		return (NULL);
	}
	ft_bzero(ret->head, size * nbr_elem);
	return (ret);
}
