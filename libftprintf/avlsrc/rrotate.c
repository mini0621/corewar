/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 16:27:19 by sunakim           #+#    #+#             */
/*   Updated: 2019/04/07 18:46:07 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_avl.h"

t_tnode	*rrotate(t_tnode *top)
{
	t_tnode *tl;
	t_tnode *tlr;

	tl = top->l;
	tlr = tl->r;
	tl->r = top;
	top->l = tlr;
	top->h = ft_max(height(top->l), height(top->r)) + 1;
	tl->h = ft_max(height(tl->l), height(tl->r)) + 1;
	return (tl);
}
