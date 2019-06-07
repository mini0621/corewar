/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:38:25 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/17 14:58:34 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "prcsfs.h"

char		*convert(va_list *ap, char **start, size_t *l)
{
	t_printops	*opt;
	t_prcs_fp	prcs;
	char		*ret;

	opt = readops(start, ap);
	if (opt->cnvrtsp == '\0')
	{
		free(opt);
		*l = 0;
		return (ft_strnew(0));
	}
	if (opt->cnvrtsp == '%')
		return (prcs_percent(opt, l));
	if (opt->cnvrtsp == 'j')
		opt->lmod = 4;
	if ((prcs = getprcsf(opt)) == NULL)
	{
		free(opt);
		return (NULL);
	}
	ret = (*prcs)(ap, opt, l);
	free(opt);
	return (ret);
}

char		*prcs_percent(t_printops *opt, size_t *l)
{
	char	*ret;

	if ((ret = ft_strdup("%")) == NULL)
		return (NULL);
	prcs_flags(opt, &ret, 0);
	if (ret == NULL)
		return (NULL);
	*l = ft_strlen(ret);
	free(opt);
	return (ret);
}

t_prcs_fp	getprcsf(t_printops *opt)
{
	char	cs;
	int		i;

	cs = opt->cnvrtsp;
	i = 0;
	while (g_prcsfs[i].cnvrt_specifier != '\0')
	{
		if (g_prcsfs[i].cnvrt_specifier == cs)
			return (g_prcsfs[i].function);
		i++;
	}
	return (NULL);
}
