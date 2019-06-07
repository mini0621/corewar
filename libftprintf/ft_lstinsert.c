/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:02:14 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/20 10:37:52 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_lstinsert(t_list **alst, t_list *new, int (*cmp)(void *, void *))
{
	t_list	*cur;
	t_list	*pre;

	if (alst == NULL)
		return ;
	if (*alst == NULL || cmp((*alst)->content, new->content) < 0)
	{
		new->next = *alst;
		*alst = new;
		return ;
	}
	cur = (*alst)->next;
	pre = *alst;
	while (cur && cmp(cur->content, new->content) > 0)
	{
		cur = cur->next;
		pre = pre->next;
	}
	new->next = cur;
	pre->next = new;
}
