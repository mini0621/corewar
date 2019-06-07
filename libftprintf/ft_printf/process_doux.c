/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dioux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:06:42 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/17 16:07:17 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*prcs_d(va_list *ap, t_printops *opt, size_t *l)
{
	t_lm		lm;
	char		*ret;
	long long	arg;
	int			sign;

	lm = opt->lmod;
	if (lm == 1)
		arg = (short)va_arg(*ap, int);
	else if (lm == 2)
		arg = (signed char)(va_arg(*ap, int));
	else if (lm == 3)
		arg = (long long)(va_arg(*ap, long));
	else if (lm == 4 || lm == 6)
		arg = (long long)(va_arg(*ap, long long));
	else
		arg = (int)va_arg(*ap, int);
	sign = (arg >= 0) ? 1 : -1;
	ret = ft_lltoa(arg);
	if (arg == 0 && opt->precision == 0)
		*ret = '\0';
	if (prcs_flags(opt, &ret, sign) == NULL)
		return (NULL);
	*l = ft_strlen(ret);
	return (ret);
}

char	*prcs_o(va_list *ap, t_printops *opt, size_t *l)
{
	t_lm				lm;
	char				*ret;
	unsigned long long	arg;
	int					sign;

	lm = opt->lmod;
	if (lm == 1)
		arg = (unsigned short)va_arg(*ap, unsigned int);
	else if (lm == 2)
		arg = (unsigned char)(va_arg(*ap, unsigned int));
	else if (lm == 3)
		arg = (unsigned long)(va_arg(*ap, unsigned long));
	else if (lm == 4 || lm == 6)
		arg = (unsigned long long)(va_arg(*ap, unsigned long long));
	else
		arg = (unsigned int)va_arg(*ap, unsigned int);
	sign = (arg > 0) ? 1 : 0;
	ret = ft_llutoa(arg, 8, 22);
	if (arg == 0 && opt->precision == 0 && (opt->flag).sharp != '#')
		*ret = '\0';
	if (prcs_flags(opt, &ret, sign) == NULL)
		return (NULL);
	*l = ft_strlen(ret);
	return (ret);
}

char	*prcs_u(va_list *ap, t_printops *opt, size_t *l)
{
	t_lm				lm;
	char				*ret;
	unsigned long long	arg;
	int					sign;

	lm = opt->lmod;
	if (lm == 1)
		arg = (unsigned short)va_arg(*ap, unsigned int);
	else if (lm == 2)
		arg = (unsigned char)(va_arg(*ap, unsigned int));
	else if (lm == 3)
		arg = (unsigned long)(va_arg(*ap, unsigned long));
	else if (lm == 4 || lm == 6)
		arg = (unsigned long long)(va_arg(*ap, unsigned long long));
	else
		arg = (unsigned int)va_arg(*ap, unsigned int);
	sign = (arg == 0) ? 0 : 1;
	ret = ft_llutoa(arg, 10, 20);
	if (arg == 0 && opt->precision == 0)
		*ret = '\0';
	if (prcs_flags(opt, &ret, sign) == NULL)
		return (NULL);
	*l = ft_strlen(ret);
	return (ret);
}

char	*prcs_x(va_list *ap, t_printops *opt, size_t *l)
{
	char				*ret;
	unsigned long long	arg;
	int					sign;

	if (opt->lmod == 1)
		arg = (unsigned short)va_arg(*ap, unsigned int);
	else if (opt->lmod == 2)
		arg = (unsigned char)(va_arg(*ap, unsigned int));
	else if (opt->lmod == 3)
		arg = (unsigned long)(va_arg(*ap, unsigned long));
	else if (opt->lmod == 4 || opt->lmod == 6)
		arg = (unsigned long long)(va_arg(*ap, unsigned long long));
	else
		arg = (unsigned int)va_arg(*ap, unsigned int);
	sign = (arg > 0) ? 1 : 0;
	ret = ft_llutoa(arg, 16, 16);
	if (arg == 0 && opt->precision == 0)
		*ret = '\0';
	if (prcs_flags(opt, &ret, sign) == NULL)
		return (NULL);
	if (opt->cnvrtsp == 'X')
		ft_strupper(ret);
	*l = ft_strlen(ret);
	return (ret);
}
