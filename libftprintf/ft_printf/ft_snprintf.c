/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:06:42 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/18 08:31:04 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_snprintf(char *str, size_t size, const char *fmt, ...)
{
	char		*output;
	va_list		ap;
	size_t		len;
	char		*start;

	if (str == NULL || fmt == NULL)
		return (-1);
	va_start(ap, fmt);
	start = (char *)fmt;
	len = 0;
	output = NULL;
	if (*fmt == '\0')
		return (0);
	if ((start = join_chars(&output, start, &len)) == NULL)
		return (-1);
	while (*start != '\0')
	{
		if ((output = join_cnvrt(&output, &start, &ap, &len)) == NULL)
			return (-1);
		if ((start = join_chars(&output, start, &len)) == NULL)
			return (-1);
	}
	va_end(ap);
	snprintoutput(str, output, len, size);
	return (len);
}

void	snprintoutput(char *str, char *output, size_t len, size_t size)
{
	if (size - 1 < len)
		len = size - 1;
	ft_memcpy(str, output, len);
	str[len] = '\0';
	free(output);
}
