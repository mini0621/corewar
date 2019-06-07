/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 22:36:35 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/12 22:25:55 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_list	*ft_lstlast(t_list *alst)
{
	t_list	*ptr;

	if (alst == NULL)
		return (NULL);
	ptr = alst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}
