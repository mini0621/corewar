/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 23:23:49 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/12 22:28:48 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && (s[i] == '\t' || s[i] == '\n' || s[i] == ' '))
		i++;
	j = ft_strlen(s) - 1;
	while (j > i && (s[j] == '\t' || s[j] == '\n' || s[j] == ' '))
		j--;
	ptr = ft_strsub(s, i, j - i + 1);
	return (ptr);
}
