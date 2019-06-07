/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avladd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:08:13 by sunakim           #+#    #+#             */
/*   Updated: 2019/05/21 17:37:51 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_avl.h"

static int		balance(t_tnode *n)
{
	if (n == NULL)
		return (0);
	return (height(n->l) - height(n->r));
}

static void		balavl(t_tnode **root, t_tnode *new, int (*cmp)(void *, void *))
{
	int b;

	b = balance((*root));
	if (b == 2)
	{
		if (cmp(new->cnt, (*root)->l->cnt) < 0)
			*root = rrotate((*root));
		else
		{
			(*root)->l = lrotate((*root)->l);
			*root = rrotate((*root));
		}
	}
	if (b == -2)
	{
		if (cmp(new->cnt, (*root)->r->cnt) > 0)
			*root = lrotate((*root));
		else
		{
			(*root)->r = rrotate((*root)->r);
			*root = lrotate((*root));
		}
	}
}

static t_tnode	*treedel_null(t_tnode **root, void (*del)(void *))
{
	ft_treedel(root, del);
	return (NULL);
}

t_tnode			*ft_avladd(t_tnode **root, t_tnode *new,
				int (*cmp)(void *, void *), void (*del)(void *))
{
	if (*root == NULL)
	{
		*root = new;
		(*root)->h = 1;
		return (*root);
	}
	if ((cmp(new->cnt, (*root)->cnt)) < 0)
	{
		if (!((*root)->l = ft_avladd(&((*root)->l), new, cmp, del)))
			return (treedel_null(root, del));
	}
	else if ((cmp(new->cnt, (*root)->cnt)) > 0)
	{
		if (!((*root)->r = ft_avladd(&((*root)->r), new, cmp, del)))
			return (treedel_null(root, del));
	}
	else
	{
		ft_treedel(&new, del);
		ft_treedel(root, del);
		return (NULL);
	}
	(*root)->h = 1 + ft_max(height((*root)->l), height((*root)->r));
	balavl(root, new, cmp);
	return (*root);
}
