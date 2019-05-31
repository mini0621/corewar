/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 22:29:37 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/12 22:30:27 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_power(int base, int power)
{
	if (power == 0)
		return (1);
	if (power < 0)
		return (1);
	return (base * ft_power(base, power - 1));
}
