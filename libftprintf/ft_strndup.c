/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:15:57 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/16 22:00:46 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	char	*ptr;

	len = ft_strlen(s1);
	if (len > n)
		len = n;
	if ((ptr = ft_memalloc((len + 1))) == NULL)
		return (NULL);
	ft_strncpy(ptr, s1, len);
	return (ptr);
}
