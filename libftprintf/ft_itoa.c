/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:04:08 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/12 22:30:20 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	powerof(int nb, int power)
{
	if (power == 0)
		return (1);
	return (nb * powerof(nb, power - 1));
}

char		*ft_itoa(int n)
{
	char	*ptr;
	int		i;
	int		neg;

	i = 0;
	if (n == -2147483648)
		return (ptr = ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	neg = (n < 0) ? 1 : 0;
	n = (n < 0) ? -n : n;
	while (i < 10 && n / powerof(10, i) != 0)
		i++;
	if ((ptr = ft_strnew(i + neg)) == NULL)
		return (NULL);
	i = i + neg - 1;
	while (i >= neg)
	{
		ptr[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	if (neg == 1)
		ptr[0] = '-';
	return (ptr);
}
