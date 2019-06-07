/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qpop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:00:34 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/17 18:07:07 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_list	*ft_qpop(t_queue *q)
{
	t_list	*ret;

	if (!(q->top))
		return (NULL);
	ret = q->top;
	if (q->last == q->top)
		q->last = NULL;
	q->top = q->top->next;
	ret->next = NULL;
	return (ret);
}
