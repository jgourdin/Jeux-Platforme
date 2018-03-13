/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:20:27 by jgourdin          #+#    #+#             */
/*   Updated: 2016/11/29 12:22:44 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t		len2;

	if (!*s2)
		return ((char*)s1);
	len2 = ft_strlen((char*)s2);
	while (*s1 && (len-- >= len2))
	{
		if (*s1 == *s2 && ft_memcmp(s1, s2, len2) == 0)
			return ((char*)s1);
		s1++;
	}
	return (NULL);
}
