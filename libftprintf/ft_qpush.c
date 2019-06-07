/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qpush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:12:04 by mnishimo          #+#    #+#             */
/*   Updated: 2019/04/18 10:57:58 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_queue	*ft_qpush(t_queue *q, t_list *nl)
{
	if (!q || !nl)
		return (NULL);
	if (!(q->top))
		q->top = nl;
	else
	{
		nl->next = q->top;
		q->top = nl;
	}
	return (q);
}
