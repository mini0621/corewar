/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:57:02 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/18 09:17:55 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			is_cnvrtsp(char c)
{
	if (c == 'i' || c == 'd' || c == 'o' || c == 'u' || c == 'x' || c == 'X'
	|| c == 'c' || c == 'f' || c == 's' || c == 'p' || c == 'e' || c == '%')
		return (1);
	if (c != 'l' && c != 'h' && c != '.' && c != 'L' && c != ' '
		&& c != ' ' && c != '#' && c != '-' && c != '+' && c != '*'
		&& ft_isdigit(c) == 0 && c != 'j')
		return (-1);
	return (0);
}

t_printops	*initoption(void)
{
	t_printops	*opt;

	if ((opt = (t_printops *)malloc(sizeof(t_printops))) == NULL)
		return (NULL);
	opt->flag.sharp = '\0';
	opt->flag.min_0 = '\0';
	opt->flag.plus_sp = '\0';
	opt->width = 0;
	opt->precision = 0xffffffffffffffff;
	opt->lmod = 0;
	opt->cnvrtsp = '\0';
	return (opt);
}

t_printops	*readops(char **start, va_list *ap)
{
	char		*i;
	t_printops	*opt;
	int			ret;

	if ((opt = initoption()) == NULL)
		return (NULL);
	i = *start + 1;
	while (*i != '\0' && (ret = is_cnvrtsp(*i)) == 0)
	{
		storeops(i, opt, ap);
		if (*i == '.' && *(i + 1) <= '9' && *(i + 1) > '0')
			i++;
		if (*i <= '9' && *i >= '1')
		{
			while (*i <= '9' && *i >= '0')
				i++;
		}
		else
			i++;
	}
	return (adjust_ops(opt, i, ret, start));
}

t_printops	*adjust_ops(t_printops *opt, char *i, int ret, char **start)
{
	char	sp;
	size_t	precision;

	opt->cnvrtsp = *i;
	if (ret == -1)
		opt->cnvrtsp = '\0';
	if (*i == '\0' || ret == -1)
		i--;
	*start = i + 1;
	precision = opt->precision;
	sp = opt->cnvrtsp;
	if (precision != 0xffffffffffffffff && (opt->flag).min_0 == '0'
	&& (sp == 'd' || sp == 'i' || sp == 'o'
		|| sp == 'u' || sp == 'x' || sp == 'X'))
		(opt->flag).min_0 = '\0';
	return (opt);
}

void		storeops(char *i, t_printops *opt, va_list *ap)
{
	opt->flag.sharp = (*i == '#') ? '#' : opt->flag.sharp;
	if ((*i == '0' && opt->flag.min_0 != '-') || *i == '-')
		opt->flag.min_0 = *i;
	if ((*i == ' ' && opt->flag.plus_sp != '+') || *i == '+')
		opt->flag.plus_sp = *i;
	if (*i <= '9' && *i > '0' && opt->width == 0)
		opt->width = ft_atozu(i);
	if (*i == 'l' && opt->lmod == none)
		opt->lmod = l;
	else if (*i == 'l' && opt->lmod != none)
		opt->lmod = ll;
	if (*i == 'h' && opt->lmod == none)
		opt->lmod = h;
	else if (*i == 'h' && opt->lmod != none)
		opt->lmod = hh;
	if (*i == 'L')
		opt->lmod = L;
	if (*i == 'j')
		opt->lmod = j;
	if (*i == '.' && *(i + 1) != '*')
		opt->precision = ft_atozu(i + 1);
	if (*i == '*' && *(i - 1) == '.')
		opt->precision = va_arg(*ap, size_t);
	if (*i == '*' && *(i - 1) != '.')
		opt->width = va_arg(*ap, size_t);
}
