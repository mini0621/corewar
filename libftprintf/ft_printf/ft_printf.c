/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:06:42 by mnishimo          #+#    #+#             */
/*   Updated: 2019/03/08 15:46:26 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *fmt, ...)
{
	char		*output;
	va_list		ap;
	size_t		len;
	char		*start;

	if (fmt == NULL)
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
	printoutput(output, len);
	return (len);
}

void	printoutput(char *output, size_t len)
{
	write(1, output, len);
	free(output);
}

char	*join_chars(char **output, char *start, size_t *len)
{
	char	*s;
	size_t	i;

	i = 0;
	while (*(start + i) != '%' && *(start + i) != '\0')
		i++;
	if (i == 0)
		return (start);
	s = *output;
	if ((*output = ft_memalloc(*len + i + 1)) == NULL)
	{
		free(s);
		return (NULL);
	}
	if (*len != 0)
		ft_memcpy(*output, s, *len);
	free(s);
	ft_memcpy(*output + *len, start, i);
	*len += i;
	return (start + i);
}

char	*join_cnvrt(char **output, char **start, va_list *ap, size_t *len)
{
	char	*ret;
	char	*s;
	size_t	slen;

	if (output == NULL || start == NULL)
		return (NULL);
	s = convert(ap, start, &slen);
	if (s == NULL || (ret = ft_memalloc(*len + slen + 1)) == NULL)
	{
		if (output != NULL && *output != NULL)
			free(*output);
		return (NULL);
	}
	if (*output != NULL)
		ft_memcpy(ret, *output, *len);
	ft_memcpy(ret + *len, s, slen);
	*len += slen;
	if (*output != NULL)
		free(*output);
	free(s);
	return (ret);
}
