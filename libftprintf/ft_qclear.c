/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qclear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:07:21 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/15 23:01:39 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_qclear(t_queue **q, void (*del)(void *, size_t))
{
	if (!q || !(*q))
		return ;
	ft_lstdel(&((*q)->top), del);
	(*q)->last = NULL;
}
