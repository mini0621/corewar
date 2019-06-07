/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qnew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 22:20:59 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/03 15:18:58 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_queue	*ft_qnew(void)
{
	t_queue	*q;

	q = (t_queue *)malloc(sizeof(t_queue));
	if (q)
	{
		q->top = NULL;
		q->last = NULL;
	}
	return (q);
}
