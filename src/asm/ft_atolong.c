/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atolong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 21:26:54 by sunakim           #+#    #+#             */
/*   Updated: 2019/06/20 20:32:50 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

long	ft_atolong(char *str)
{
	int		i;
	long	ret;
	long	neg;

	i = 0;
	neg = 1;
	while (str[i] != '\0' && (str[i] == '\t' || str[i] == '\n' || str[i] == ' '
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	ret = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	return (ret * neg);
}
