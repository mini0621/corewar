/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:06:42 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/18 08:36:02 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_asprintf(char **ret, const char *fmt, ...)
{
	va_list		ap;
	size_t		len;
	char		*start;

	if (ret == NULL || fmt == NULL)
		return (-1);
	va_start(ap, fmt);
	start = (char *)fmt;
	len = 0;
	*ret = NULL;
	if (*fmt == '\0')
		return (0);
	if ((start = join_chars(ret, start, &len)) == NULL)
		return (asprinterror(ret));
	while (*start != '\0')
	{
		if ((*ret = join_cnvrt(ret, &start, &ap, &len)) == NULL)
			return (-1);
		if ((start = join_chars(ret, start, &len)) == NULL)
			return (asprinterror(ret));
	}
	va_end(ap);
	return (len);
}

int		asprinterror(char **ret)
{
	ret = NULL;
	(void)ret;
	return (-1);
}
