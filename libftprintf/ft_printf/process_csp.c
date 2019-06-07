/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_csp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:58:39 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/18 09:31:24 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*prcs_c(va_list *ap, t_printops *opt, size_t *l)
{
	char	c;
	char	*ret;
	char	*tmp;
	int		terminate;

	c = (char)va_arg(*ap, int);
	terminate = (c == '\0') ? 1 : 0;
	c = (terminate == 1) ? 'A' : c;
	if ((ret = ft_strnew(1)) == NULL)
		return (NULL);
	ft_strncpy(ret, &c, 1);
	if (prcs_cflags(opt, &ret, l) == NULL)
		return (NULL);
	if (terminate == 1 && (tmp = ft_strchr(ret, 'A')) != NULL)
		*tmp = '\0';
	return (ret);
}

char	*prcs_s(va_list *ap, t_printops *opt, size_t *l)
{
	char	*s;
	char	*ret;

	s = va_arg(*ap, char *);
	if (s == NULL)
		ret = ft_strdup("(null)");
	else
		ret = ft_strdup(s);
	if (prcs_flags(opt, &ret, 0) == NULL)
		return (NULL);
	*l = ft_strlen(ret);
	return (ret);
}

char	*prcs_p(va_list *ap, t_printops *opt, size_t *l)
{
	char				*ret;
	unsigned long long	arg;

	arg = (unsigned long long)va_arg(*ap, void *);
	(opt->flag).sharp = '#';
	if ((ret = ft_llutoa(arg, 16, 16)) == NULL)
		return (NULL);
	if (arg == 0 && opt->precision == 0)
		*ret = '\0';
	if (prcs_flags(opt, &ret, 1) == NULL)
		return (NULL);
	*l = ft_strlen(ret);
	return (ret);
}

char	*prcs_cflags(t_printops *opt, char **s, size_t *l)
{
	size_t	w;
	char	*ret;
	char	a;

	*l = 1;
	w = opt->width;
	a = ((opt->flag).min_0 == '0') ? '0' : ' ';
	if (w < 1)
		return (*s);
	if (s == NULL || *s == NULL || (ret = ft_strnew(w)) == NULL)
		return (NULL);
	if ((opt->flag).min_0 == '-')
	{
		ft_memcpy(ret, *s, 1);
		ft_memset(ret + 1, ' ', w - 1);
	}
	else
	{
		ft_memset(ret, a, w - 1);
		ft_memcpy(ret + w - 1, *s, 1);
	}
	*l = w;
	free(*s);
	*s = ret;
	return (ret);
}
