/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 23:12:28 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/12 22:23:42 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ptr = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strcat(ptr, s1);
	ft_strcat(ptr, s2);
	return (ptr);
}
