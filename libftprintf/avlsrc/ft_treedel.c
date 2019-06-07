/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treedel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:35:59 by sunakim           #+#    #+#             */
/*   Updated: 2019/04/07 18:45:38 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_avl.h"

static void	ft_nodedel(t_tnode *node, void (del)(void *))
{
	if (node != NULL)
	{
		ft_nodedel(node->l, del);
		ft_nodedel(node->r, del);
		if (del != NULL)
			del(node->cnt);
		free(node);
		node = NULL;
	}
}

void		ft_treedel(t_tnode **root, void (del)(void *))
{
	if (*root != NULL)
	{
		ft_nodedel(*root, del);
		*root = NULL;
	}
}
