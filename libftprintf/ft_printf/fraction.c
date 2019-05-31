/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fraction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 18:49:16 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/18 18:23:53 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	*init_frac(uint64_t frac)
{
	unsigned long long	*a;

	if ((a = (unsigned long long*)malloc(sizeof(unsigned long long) * 101))
			== NULL)
		return (NULL);
	ft_bzero(a, sizeof(unsigned long long) * 101);
	if (frac == 0)
	{
		a[57] = 10000;
		return (a);
	}
	a[50] = (unsigned long long)frac % 100000000;
	a[51] = ((unsigned long long)frac / 100000000) % 100000000;
	a[52] = (unsigned long long)frac / 10000000000000000;
	return (a);
}

char				*get_frac10(t_double *n, int frac_bits, int subnormal)
{
	unsigned long long	*a;
	short				expo;
	int					e;

	if (n == NULL)
		return (NULL);
	e = 0;
	expo = n->expo;
	a = init_frac(n->frac);
	if (a == NULL)
		return (NULL);
	if (n->frac != 0)
		mult_frac(a, 5, frac_bits);
	if (subnormal == 1)
		div_frac(a, 1022);
	else if (expo > 0)
		mult_frac(a, 2, (int)expo);
	else if (expo < 0)
		e = div_frac(a, -(int)(expo));
	return (fractoa(a, e));
}

char				*fractoa(unsigned long long *frac, int e)
{
	int		i;
	char	*ret;
	char	*s;

	if ((ret = ft_strnew(0)) == NULL)
		return (NULL);
	while (e > 0)
	{
		s = ft_strdup("00000000");
		ret = ft_strjoinfree(&ret, &s, 3);
		e--;
	}
	i = 100;
	while (i < 100 && frac[i] != 0)
		i++;
	while (i != 0)
	{
		s = ft_llutoa(frac[i], 10, 20);
		s = prcs_precision(&s, 8, 1);
		if ((ret = ft_strjoinfree(&ret, &s, 3)) == NULL)
			return (NULL);
		i--;
	}
	free(frac);
	return (ret);
}

int					shift_frac_left(unsigned long long *a)
{
	int	e;
	int i;

	e = 100;
	while (e >= 0 && a[e] == 0)
		e--;
	if (e == 100)
		return (0);
	i = 100;
	while (e >= 0)
	{
		a[i] = a[e];
		i--;
		e--;
	}
	while (i >= 0)
	{
		a[i] = 0;
		i--;
	}
	return (e);
}

int					get10th_expo(uint16_t expo)
{
	long double	p;
	int			i;

	p = (short)(expo);
	if (p == 1 || p == 0)
		return (1);
	p = (p * 0.301029999566L);
	i = (int)p;
	if (p == i)
		return (i);
	if (p >= i)
		i = (i + 1 - p < p - i) ? i + 1 : i;
	else
		i = (p - i + 1 < p - 1) ? i - 1 : i;
	if (i > 1)
		return (i + 1);
	return (i);
}
