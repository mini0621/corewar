/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 23:02:24 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/16 02:30:39 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strsubfree(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	ptr = (char *)malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	free(s);
	ptr[i] = '\0';
	return (ptr);
}
