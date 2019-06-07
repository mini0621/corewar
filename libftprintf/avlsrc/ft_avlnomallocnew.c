/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avlnomallocnew.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:41:40 by sunakim           #+#    #+#             */
/*   Updated: 2019/05/25 15:18:54 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_avl.h"

t_tnode	*ft_avlnomallocnew(void const *content)
{
	t_tnode *new;

	if (!(new = ft_avlnew(NULL, 0)))
		return (NULL);
	new->cnt = (void *)content;
	return (new);
}
