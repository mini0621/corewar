/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avlfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 14:38:57 by sunakim           #+#    #+#             */
/*   Updated: 2019/04/07 18:44:19 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_avl.h"

t_tnode	*ft_avlfind(t_tnode *root, void *value, int (*cmp)(void *, void *))
{
	if (root == NULL)
		return (NULL);
	while (root != NULL)
	{
		if ((cmp(value, root->cnt)) == 0)
			return (root);
		else if ((cmp(value, root->cnt)) < 0)
			root = root->l;
		else
			root = root->r;
	}
	return (NULL);
}
