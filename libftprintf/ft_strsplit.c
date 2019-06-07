/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 23:43:30 by mnishimo          #+#    #+#             */
/*   Updated: 2019/03/30 13:47:35 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	countwords(char const *s, char c)
{
	int	i;
	int	wc;

	if (s == NULL || s[0] == '\0')
		return (0);
	i = 0;
	wc = 0;
	if (s[i] != c)
		wc++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			wc++;
		i++;
	}
	return (wc);
}

static char	*trim(char const *s, char c, int *start)
{
	int		j;
	char	*ptr;
	int		i;

	i = *start;
	while (s[i] != '\0' && s[i] == c)
		i++;
	j = i;
	while (s[j] != '\0' && s[j] != c)
		j++;
	ptr = ft_strsub(s, i, j - i);
	if (ptr == NULL)
		return (NULL);
	*start = i;
	return (ptr);
}

static void	delete(char **s, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char		**ft_strsplit(char const *s, char c)
{
	int		wc;
	char	**ret;
	int		i;
	int		j;

	wc = countwords(s, c);
	if (!(ret = (char **)malloc(sizeof(char *) * (wc + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (i++ < wc - 1)
	{
		ret[i] = trim(s, c, &j);
		if (ret[i] == NULL)
		{
			delete(ret, i);
			return (NULL);
		}
		while (s[j] != c && s[j] != '\0')
			j++;
	}
	ret[i] = NULL;
	return (ret);
}
