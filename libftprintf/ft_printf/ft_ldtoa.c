/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:21:57 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/18 18:44:52 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		add_zeros(char **s, int point)
{
	char	*tmp;

	if ((tmp = ft_strnew(-point)) == NULL)
	{
		free(*s);
		return (-1);
	}
	ft_memset(tmp, '0', -point);
	if ((*s = ft_strjoinfree(&tmp, s, 3)) == NULL)
		return (-1);
	return (0);
}

char	*ft_ldtoa(t_double *n, size_t precision, int e)
{
	char	*ret;
	char	*integer;
	int		p;

	if ((ret = get_frac10(n, 63, 0)) == NULL)
		return (NULL);
	p = get10th_expo(n->expo);
	if (e == 1)
		return (ft_strsubfree(ret, skip_zeros(ret), precision + 2));
	if (p < 0)
		ret = ft_strsubfree(ret, skip_zeros(ret), precision + 1);
	if ((ret = ft_strsubfree(ret, skip_zeros(ret),
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

int		round_s(char **s, int point, size_t precision)
{
	size_t	index;

	index = (point < 0) ? precision : (unsigned int)point + precision;
	if (ft_strlen(*s) <= index + 1)
		return (0);
	if (*(*s + index + 1) < '5')
		return (0);
	while (index > 0)
	{
		if (*(*s + index) != '9')
		{
			*(*s + index) += 1;
			return (0);
		}
		*(*s + index) = '0';
		index--;
	}
	if (*(*s + index) != '9')
	{
		*(*s + index) += 1;
		return (0);
	}
	return (1);
}

int		skip_zeros(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '0')
		i++;
	return (i);
}

char	*sub_integer(char **s, int point, int precision)
{
	char	*ret;
	char	*tmp;

	if (point < 0)
		point = add_zeros(s, point);
	if (point < 0)
		return (NULL);
	if (round_s(s, point, precision) == 1)
		ret = ft_strdup("1");
	else if (point == 0)
		ret = ft_strdup("0");
	if (point > 0)
		ret = ft_strsub(*s, 0, (size_t)point);
	if (point > 0)
		*s = ft_strsubfree(*s, (size_t)point, precision);
	if (precision != 0)
	{
		tmp = ft_strdup(".");
		ret = ft_strjoinfree(&ret, &tmp, 3);
	}
	else
		free(*s);
	return (ret);
}
