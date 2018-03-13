/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 14:43:24 by jgourdin          #+#    #+#             */
/*   Updated: 2017/09/08 05:37:42 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_length(int i, char const *s, char c)
{
	int		lengthword;

	lengthword = i;
	while (s[lengthword] != c && s[lengthword] != '\0')
		lengthword++;
	lengthword = lengthword - i;
	return (lengthword);
}

static int		ft_countword(char const *s, char c)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			word++;
		}
	}
	return (word);
}

static char		**ft_do_split(int i, char const *s, char c, char **str)
{
	int		lengthword;
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			lengthword = ft_count_length(i, s, c);
			str[j] = (char *)malloc(lengthword + 1);
			while (lengthword-- > 0)
				str[j][k++] = s[i++];
			str[j++][k] = '\0';
			k = 0;
			lengthword = 0;
		}
	}
	str[j] = NULL;
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	int		j;
	char	**str;
	char	*str2;
	int		index;
	int		word;

	index = 0;
	j = 0;
	if (c && s)
	{
		word = ft_countword(s, c);
		str = (char **)malloc((word + 1) * sizeof(char *));
		if (str == 0)
			return (0);
		str = ft_do_split(index, s, c, str);
		return (str);
	}
	else
	{
		str2 = ft_strnew(1);
		return ((char **)str2);
	}
}
