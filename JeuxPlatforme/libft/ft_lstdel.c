/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 14:30:52 by jgourdin          #+#    #+#             */
/*   Updated: 2016/12/06 18:20:46 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*lst;
	t_list	*lstnext;

	lst = *alst;
	while (lst)
	{
		lstnext = lst->next;
		del(lst->content, lst->content_size);
		free(lst);
		lst = lstnext;
	}
	*alst = NULL;
}
