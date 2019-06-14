/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:40:02 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/13 20:48:16 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_lstadd(t_list **alst, t_list *new)
{
	if (!new || !alst)
		return (0);
	new->next = *alst;
	*alst = new;
	return (1);
}
