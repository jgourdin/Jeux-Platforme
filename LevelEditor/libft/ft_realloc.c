/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 00:49:01 by jgourdin          #+#    #+#             */
/*   Updated: 2017/03/21 00:50:14 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t o_size, size_t n_size)
{
	void	*new;

	if (n_size == 0)
	{
		ft_memdel(&ptr);
		return (NULL);
	}
	if (!(new = ft_memalloc(n_size)))
		return (NULL);
	if (ptr && o_size)
	{
		if (o_size > n_size)
			ft_memcpy(new, ptr, n_size);
		else
			ft_memcpy(new, ptr, o_size);
		ft_memdel(&ptr);
	}
	return (new);
}
