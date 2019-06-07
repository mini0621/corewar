/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:59:51 by mnishimo          #+#    #+#             */
/*   Updated: 2019/03/27 19:56:24 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*prcs_ld(va_list *ap, t_printops *opt, int *sign)
{
	long double	arg;
	t_double	*n;
	char		*s;
	char		*ret;

	arg = va_arg(*ap, long double);
	if ((n = get_ldouble(arg)) == NULL)
		return (NULL);
	*sign = (arg == 0) ? 0 : n->sign;
	if (n->expo == 0x4000)
		ret = sp_double(n->sign, n->frac);
	else if (arg == 0 || (opt->precision < 7 && arg < 1000000000000000
				&& arg > -1000000000000000))
		ret = ft_ldtolltoa(arg, opt->precision);
	else
		ret = ft_ldtoa(n, opt->precision, 0);
	if (*sign < 0)
	{
		s = ft_strdup("-");
		ret = ft_strjoinfree(&s, &ret, 3);
	}
	free(n);
	return (ret);
}

t_double	*get_ldouble(long double n)
{
	t_double *d;
	uint16_t c;

	if ((d = (t_double *)malloc(sizeof(t_double))) == NULL)
		return (NULL);
	if ((short)(c = *((uint16_t*)&n + 4)) < 0)
		d->sign = -1;
	else
		d->sign = 1;
	d->expo = (c & 0x7fff) - 16383;
	d->frac = *((uint64_t*)&n);
	return (d);
}
