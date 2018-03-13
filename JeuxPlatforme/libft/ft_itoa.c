/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:19:29 by jgourdin          #+#    #+#             */
/*   Updated: 2016/12/01 15:05:12 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	itoa_isnegative(char *s, int *n)
{
	*n *= -1;
	s[0] = '-';
}

char		*ft_itoa(int n)
{
	int		i;
	int		tmp;
	char	*str;

	i = 1;
	tmp = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	while (tmp /= 10)
		++i;
	if (n < 0)
		++i;
	if ((str = (char *)malloc(i + 1)) == NULL)
		return (NULL);
	if (n < 0)
		itoa_isnegative(str, &n);
	str[i] = '\0';
	while (i-- && n)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
