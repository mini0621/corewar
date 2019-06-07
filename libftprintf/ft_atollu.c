/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atollu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:31:04 by mnishimo          #+#    #+#             */
/*   Updated: 2019/04/07 18:48:01 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned long long int	ft_atollu(const char *str)
{
	int						i;
	unsigned long long int	ret;
	unsigned long long int	neg;

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
