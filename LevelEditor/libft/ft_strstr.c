/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:44:02 by jgourdin          #+#    #+#             */
/*   Updated: 2016/11/29 12:31:14 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *meule_de_foin, const char *aiguille)
{
	int	i;
	int	j;

	i = 0;
	if (aiguille[0] == '\0')
		return ((char *)meule_de_foin);
	while (meule_de_foin[i])
	{
		j = 0;
		while (aiguille[j] == meule_de_foin[i + j])
		{
			if (aiguille[j + 1] == '\0')
				return ((char *)meule_de_foin + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
