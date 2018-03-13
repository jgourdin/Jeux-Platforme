/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 01:13:49 by jgourdin          #+#    #+#             */
/*   Updated: 2017/09/08 06:47:26 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char		*stockoline(char **stock, char **line)
{
	char		*tmp;
	size_t		len;

	len = 0;
	while (*stock && (*stock)[len] && (*stock)[len] != '\n')
		len++;
	if (!(*line = ft_strnew(sizeof(**line) * len)))
		return (NULL);
	(*stock ? *line = ft_strncpy(*line, *stock, len) : (char*)0);
	if (!*stock || !((*stock)[len]))
	{
		if (*stock)
			ft_strdel(stock);
		if (len == 0)
			return (NULL);
		return (*line);
	}
	if (!(tmp = ft_strnew(sizeof(*tmp) * (ft_strlen(*stock) - len - 1))))
		return (NULL);
	tmp = ft_strcpy(tmp, *stock + len + 1);
	free(*stock);
	*stock = tmp;
	return (*line);
}

static int		bufftostock(char *buff, char **stock, size_t size)
{
	size_t		o_len;
	size_t		po;

	o_len = (*stock ? ft_strlen(*stock) : 0);
	if (!(*stock = ft_realloc(*stock, o_len + 1, o_len + size + 2)))
		return (-1);
	po = size;
	while (size--)
	{
		(*stock)[o_len++] = *buff;
		buff++;
	}
	(*stock)[o_len] = '\0';
	return (ft_strchr(*stock, '\n') || po < BUFF_SIZE ? 1 : 0);
}

int				get_next_line(const int fd, char **line)
{
	char		*buff;
	static char	*stock = NULL;
	int			flg;
	ssize_t		ret;

	if (line == NULL)
		return (-1);
	(flg = (stock && ft_strchr(stock, '\n')) ? 1 : 0);
	if (!(buff = ft_memalloc(BUFF_SIZE + 1)))
		return (-1);
	while (!flg && (ret = read(fd, buff, BUFF_SIZE)) > 0)
		flg = bufftostock(buff, &stock, ret);
	ft_memdel((void**)&buff);
	if (flg == -1 || ret == -1)
		return (-1);
	if (flg >= 0)
		*line = stockoline(&stock, line);
	if (flg == 0 && ret == 0 && (!stock) && !*line)
		return (0);
	return (1);
}
