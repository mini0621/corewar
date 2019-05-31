/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 16:27:39 by sunakim           #+#    #+#             */
/*   Updated: 2019/04/07 18:46:02 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_avl.h"

t_tnode	*lrotate(t_tnode *top)
{
	t_tnode *tr;
	t_tnode *trl;

	tr = top->r;
	trl = tr->l;
	tr->l = top;
	top->r = trl;
	top->h = ft_max(height(top->l), height(top->r)) + 1;
	tr->h = ft_max(height(tr->l), height(tr->r)) + 1;
	return (tr);
}
