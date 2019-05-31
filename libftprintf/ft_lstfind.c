/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:02:07 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/12 22:30:53 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_list	*ft_lstfind(t_list *alst, void *content, int (*cmp)(void *, void *))
{
	t_list	*cur;

	if (alst == NULL)
		return (NULL);
	cur = alst;
	while (cur != 0)
	{
		if ((*cmp)(cur->content, content) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
