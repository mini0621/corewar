/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 23:12:11 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/18 18:12:05 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*prcs_flags(t_printops *opt, char **s, int sign)
{
	t_flags	flags;
	char	sp;

	flags = opt->flag;
	sp = opt->cnvrtsp;
	if (s == NULL || *s == NULL)
		return (NULL);
	if (sp == 's' && (*s = prcs_precision_s(s, opt->precision)) == NULL)
		return (NULL);
	if ((sp == 'd' || sp == 'i' || sp == 'o' || sp == 'u' || sp == 'x'
				|| sp == 'X' || sp == 'p')
			&& (*s = prcs_precision(s, opt->precision, sign)) == NULL)
		return (NULL);
	if (sign > 0 && flags.sharp == '#' && (*s = prcs_sharp(sp, s)) == NULL)
		return (NULL);
	if (sign > 0 && flags.plus_sp != '\0'
			&& (*s = prcs_plus(sp, s, flags.plus_sp)) == NULL)
		return (NULL);
	if (flags.min_0 == '0' && opt->width > 0
			&& (*s = prcs_zero(sp, s, opt->width, &flags)) == NULL)
		return (NULL);
	if (opt->width > 0 && (*s = prcs_min(s, opt->width, flags.min_0)) == NULL)
		return (NULL);
	return (*s);
}

char	*prcs_sharp(char sp, char **s)
{
	char	*ret;

	if (sp == 'o')
	{
		ret = ft_strdup("0");
		return (ft_strjoinfree(&ret, s, 3));
	}
	else if (sp == 'x' || sp == 'X' || sp == 'p')
	{
		ret = ft_strdup("0x");
		return (ft_strjoinfree(&ret, s, 3));
	}
	else
		return (*s);
}

char	*prcs_plus(char sp, char **s, char c)
{
	char	*ret;

	if ((sp == 'd' || sp == 'i' || sp == 'f' || sp == 'e')
		&& ft_strncmp(*s, "nan", 3) != 0)
	{
		ret = ft_strnew(ft_strlen(*s) + 1);
		if (ret != NULL)
		{
			ft_memset(ret, c, 1);
		}
		return (ft_strjoinfree(&ret, s, 3));
	}
	return (*s);
}

char	*prcs_zero(char sp, char **s, size_t w, t_flags *flags)
{
	char	*ret;
	size_t	i;

	if (sp == 'p' || ft_strlen(*s) >= w
			|| ft_strchr(*s, 'n') != NULL)
		return (*s);
	if ((ret = ft_strnew(w)) == NULL)
	{
		free(*s);
		return (NULL);
	}
	if (flags->sharp == '#' && sp == 'x')
		i = 2;
	else if (**s == '-' || **s == '+' || **s == ' ')
		i = 1;
	else
		i = 0;
	if (i != 0)
		ft_strncpy(ret, *s, i);
	ft_memset(ret + i, '0', (w - ft_strlen(*s)) * sizeof(char));
	ft_strcat(ret, *s + i);
	free(*s);
	return (ret);
}

char	*prcs_min(char **s, size_t w, char min)
{
	char	*ret;
	size_t	len;

	if (w == 0 || (w < ft_strlen(*s)))
		return (*s);
	len = w - ft_strlen(*s);
	if ((ret = ft_strnew(len)) == NULL)
		return (NULL);
	ft_memset(ret, ' ', len);
	if (min == '-')
		return (ft_strjoinfree(s, &ret, 3));
	return (ft_strjoinfree(&ret, s, 3));
}
