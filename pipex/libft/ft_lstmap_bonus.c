/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:27:14 by aezzahir          #+#    #+#             */
/*   Updated: 2024/03/23 15:24:10 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, int (*f)(int))
{
	t_list	*new_list;
	t_list	*new_node;
	int		new_n;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_n = (*f)(lst->n);
		new_node = ft_lstnew(new_n);
		if (!new_node)
		{
			ft_lstclear(&new_list);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
