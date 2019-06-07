/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qdel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:07:21 by mnishimo          #+#    #+#             */
/*   Updated: 2019/04/16 16:11:48 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_qdel(t_queue **q, void (*del)(void *, size_t))
{
	if (!q || !(*q))
		return ;
	ft_lstdel(&((*q)->top), del);
	(*q)->last = NULL;
	free(*q);
	*q = NULL;
}
