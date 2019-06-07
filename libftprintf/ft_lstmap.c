/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:45:28 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/12 22:29:52 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ptr;
	t_list	*first;

	first = f(lst);
	lst = lst->next;
	ptr = first;
	while (lst != NULL)
	{
		ptr->next = f(lst);
		ptr = ptr->next;
		lst = lst->next;
	}
	return (first);
}
