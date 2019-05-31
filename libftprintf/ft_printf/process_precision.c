/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_precision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:06:47 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/17 16:26:53 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*prcs_precision(char **s, size_t precision, int sign)
{
	char	*ret;
	size_t	len;

	len = (sign < 0) ? ft_strlen(*s) - 1 : ft_strlen(*s);
	if (precision == 0xffffffffffffffff || len >= precision)
		return (*s);
	if ((ret = ft_strnew(precision + ft_strlen(*s))) == NULL)
	{
		free(*s);
		return (NULL);
	}
	if (sign < 0)
	{
		precision = precision - len;
		*ret = '-';
		ft_memset(ret + 1, '0', precision * sizeof(char));
		ft_strcpy(ret + 1 + precision, *s + 1);
	}
	else
	{
		ft_memset(ret, '0', (precision - ft_strlen(*s)) * sizeof(char));
		ft_strcat(ret, *s);
	}
	free(*s);
	return (ret);
}

char	*prcs_precision_s(char **s, size_t precision)
{
	if (precision == 0)
	{
		**s = '\0';
		return (*s);
	}
	if (**s == '\0')
		return (*s);
	if (precision == 0xffffffffffffffff)
		return (*s);
	*s = ft_strsubfree(*s, 0, precision);
	return (*s);
}

char	*prcs_precision_end(char **s, size_t precision)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(*s);
	if (len >= precision)
		return (*s);
	precision -= len;
	if ((ret = ft_strnew(precision)) == NULL)
	{
		free(*s);
		return (NULL);
	}
	ft_memset(ret, '0', precision * sizeof(char));
	*s = ft_strjoinfree(s, &ret, 3);
	return (*s);
}
