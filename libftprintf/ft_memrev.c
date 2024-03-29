/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 15:03:52 by allefebv          #+#    #+#             */
/*   Updated: 2019/07/01 11:21:50 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_memrev(void *str, size_t len)
{
	size_t	i;
	char	temp;

	temp = 0;
	i = 0;
	while (i < len)
	{
		temp = *(char*)(str + (len - 1));
		*(char*)(str + (len - 1)) = *(char*)(str + i);
		*(char*)(str + i) = temp;
		i++;
		len--;
	}
}
