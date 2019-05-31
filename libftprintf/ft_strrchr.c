/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:56:40 by mnishimo          #+#    #+#             */
/*   Updated: 2018/11/29 10:24:04 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	ptr = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			ptr = (char *)s + i;
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	else
		return (ptr);
}
