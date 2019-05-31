/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 22:03:21 by mnishimo          #+#    #+#             */
/*   Updated: 2019/04/07 18:52:21 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static	void	ft_swap(void *ptr1, void *ptr2)
{
	void	*tmp;

	tmp = ptr1;
	ptr1 = ptr2;
	ptr2 = tmp;
}

static	t_list	*insertion_swap(t_list *index, t_list **sorted)
{
	void	*tmp;

	if (index == *sorted)
	{
		*sorted = (*sorted)->next;
		return (*sorted);
	}
	tmp = (*sorted)->content;
	(*sorted)->content = index->content;
	index->content = tmp;
	*sorted = (*sorted)->next;
	return ((*sorted));
}

void			ft_lstsort(t_list **alist, int (*cmp)(void *, void *))
{
	t_list	*index;
	t_list	*cur;
	t_list	*sorted;

	if (!alist || !(*alist) || !((*alist)->next))
		return ;
	sorted = *alist;
	cur = *alist;
	if (!cur->next->next && cmp(cur->content, cur->next->content) > 0)
		ft_swap(cur->content, cur->next->content);
	while (cur)
	{
		index = sorted;
		while (cur)
		{
			if (cmp(cur->content, index->content) < 0)
				index = cur;
			cur = cur->next;
		}
		cur = insertion_swap(index, &sorted);
	}
}
