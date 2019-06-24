/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:42:24 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/24 14:44:15 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_arrdel(t_arr **arr)
{
	if (!arr || !(*arr))
		return ;
	if ((*arr)->head)
		free((*arr)->head);
	free(*arr);
	*arr = NULL;
}
