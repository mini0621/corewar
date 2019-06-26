/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:02:14 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/26 16:23:49 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_lstpushback(t_list **alst, t_list *new)
{
	t_list	*current;

	if (alst == NULL || new == NULL)
	{
		if (new)
			free(new);
		return (0);
	}
	if (*alst == NULL)
	{
		*alst = new;
		return (1);
	}
	current = *alst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	return (1);
}
