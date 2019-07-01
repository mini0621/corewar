/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_parser_util_sub.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 10:32:08 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/01 13:24:54 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int		dis_endian_conversion(unsigned int value)
{
	return (((value >> 24) & 0x0ff)
			| ((value << 8) & 0xff0000)
			| ((value >> 8) & 0xff00)
			| ((value << 24) & 0xff000000));
}

int					dis_check_endianness(int value)
{
	char			*str;

	str = (char *)&value;
	return ((*str == 1) ? 1 : 0);
}

int16_t				dis_endian_convert_16(int16_t val)
{
	return ((val << 8) | ((val >> 8) & 0xff));
}

int32_t				dis_endian_convert_32(int32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | ((val >> 16) & 0xFFFF);
}
