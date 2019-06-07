/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:19:46 by mnishimo          #+#    #+#             */
/*   Updated: 2019/04/09 23:09:09 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*lst;

	lst = *alst;
	if (del)
		del(lst->content, lst->content_size);
	free(*alst);
	*alst = NULL;
}
