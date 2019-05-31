/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:59:51 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/18 18:45:18 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*prcs_f(va_list *ap, t_printops *opt, size_t *l)
{
	char	*ret;
	t_lm	lm;
	int		sign;

	if (opt->precision == 0xffffffffffffffff)
		opt->precision = 6;
	lm = opt->lmod;
	ret = NULL;
	if (lm == 5)
		ret = prcs_ld(ap, opt, &sign);
	else
		ret = prcs_db(ap, opt, &sign);
	ret = prcs_flags(opt, &ret, sign);
	if (ret == NULL)
		return (NULL);
	*l = ft_strlen(ret);
	return (ret);
}

char		*prcs_db(va_list *ap, t_printops *opt, int *sign)
{
	double		arg;
	t_double	*n;
	char		*ret;
	char		*s;

	arg = va_arg(*ap, double);
	if ((n = get_double(arg)) == NULL)
		return (NULL);
	*sign = (arg == 0) ? 0 : n->sign;
	if (n->expo == 1024)
		ret = sp_double(n->sign, n->frac);
	else if (arg == 0 || (opt->precision < 7 && arg < 1000000000000000
				&& arg > -1000000000000000))
		ret = ft_ldtolltoa((long double)arg, opt->precision);
	else
		ret = ft_dbtoa(n, opt->precision, 0);
	if (*sign < 0)
	{
		s = ft_strdup("-");
		ret = ft_strjoinfree(&s, &ret, 3);
	}
	free(n);
	return (ret);
}

t_double	*get_double(double n)
{
	t_double *d;
	uint16_t c;

	if ((d = (t_double *)malloc(sizeof(t_double))) == NULL)
		return (NULL);
	if ((c = *((uint16_t*)&n + 3)) > 0x7fff)
		d->sign = -1;
	else
		d->sign = 1;
	d->expo = (((c & 0x7fff) >> 4) - 1023);
	d->frac = *((uint64_t*)&n);
	d->frac = d->frac & 0x000fffffffffffff;
	if ((short)d->expo != -1023)
		d->frac = d->frac | 0x0010000000000000;
	return (d);
}

char		*sp_double(int sign, uint64_t frac)
{
	if (frac != 0 && frac != 0x8000000000000000)
		return (ft_strdup("nan"));
	sign++;
	return (ft_strdup("inf"));
}
