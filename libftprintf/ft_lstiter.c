/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:43:04 by mnishimo          #+#    #+#             */
/*   Updated: 2019/04/09 23:15:01 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*cur;

	cur = lst;
	while (cur)
	{
		f(cur);
		cur = cur->next;
	}
}
