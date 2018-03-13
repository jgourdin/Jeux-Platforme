/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 13:39:44 by jgourdin          #+#    #+#             */
/*   Updated: 2016/12/01 14:49:24 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	len;
	char	*str;

	if (!s)
		return (NULL);
	len = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	len = ft_strlen(s);
	while ((s[len - 1] == ' ' || s[len - 1] == '\t' || s[len - 1] == '\n')
			&& len)
		len--;
	if (!(str = (char *)malloc(len + 1)))
		return (NULL);
	str[len] = '\0';
	while (len)
	{
		len--;
		str[len] = s[len];
	}
	return (str);
}
