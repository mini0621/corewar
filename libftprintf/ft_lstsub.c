/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:18:33 by mnishimo          #+#    #+#             */
/*   Updated: 2019/04/22 16:24:08 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_list	*ft_lstsub(t_list **top, t_list *tar)
{
	t_list	*cur;

	if (!top || !(*top) || !tar)
		return (NULL);
	if (*top == tar)
	{
		*top = (*top)->next;
		return (tar);
	}
	cur = *top;
	while (cur && cur->next && cur->next != tar)
		cur = cur->next;
	if (!cur || !cur->next)
		return (NULL);
	cur->next = tar->next;
	return (tar);
}
