/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:21:57 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/18 18:22:58 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_dbtoa(t_double *n, size_t precision, int e)
{
	char	*ret;
	char	*integer;
	int		p;
	int		subnormal;

	subnormal = ((short)n->expo == -1023) ? 1 : 0;
	if ((ret = get_frac10(n, 52, subnormal)) == NULL)
		return (NULL);
	p = get10th_expo(n->expo) - subnormal;
	if (e == 1)
		return (ft_strsubfree(ret, skip_zeros(ret), precision + 2));
	if (p < 0)
		ret = ft_strsubfree(ret, skip_zeros(ret), precision + 1);
	else if ((ret = ft_strsubfree(ret, skip_zeros(ret),
					(size_t)p + precision + 1)) == NULL)
		return (NULL);
	integer = sub_integer(&ret, p, precision);
	if (precision == 0)
		return (integer);
	if ((ret = ft_strsubfree(ret, 0, precision)) == NULL)
		return (NULL);
	if (ft_strlen(ret) < precision)
		ret = prcs_precision_end(&ret, precision);
	ret = ft_strjoinfree(&integer, &ret, 3);
	return (ret);
}
