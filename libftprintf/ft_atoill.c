/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 14:13:23 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/05/30 14:13:42 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int				ft_isspace(int c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == ' ' || c == '\v' || c
			== '\r')
		return (1);
	return (0);
}

unsigned long long int    ft_atoill(const char *str)
{
    int                        i;
    unsigned long long int    ret;
    unsigned long long int    neg;

    i = 0;
    neg = 1;
    while (ft_isspace(str[i]))
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