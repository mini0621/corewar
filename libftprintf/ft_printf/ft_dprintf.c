/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:06:42 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/17 18:04:06 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_dprintf(int fd, const char *fmt, ...)
{
	char		*output;
	va_list		ap;
	size_t		len;
	char		*start;

	if (fd < 0 || fmt == NULL)
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
	dprintoutput(fd, output, len);
	return (len);
}

void	dprintoutput(int fd, char *output, size_t len)
{
	write(fd, output, len);
	free(output);
}
