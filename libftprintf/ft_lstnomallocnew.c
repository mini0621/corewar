/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnomallocnew.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:12:04 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/25 14:39:15 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_list	*ft_lstnomallocnew(void const *content, size_t content_size)
{
	t_list	*ptr;

	if (!(ptr = ft_lstnew(NULL, 0)))
		return (NULL);
	ptr->content = (void *)content;
	ptr->content_size = content_size;
	return (ptr);
}
