/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 13:49:35 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/29 14:35:41 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*node;
	t_list	*last;
	void	*content;

	new = NULL;
	last = NULL;
	while (lst != NULL)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (node == NULL)
		{
			del(content);
			ft_lstclear(&new, del);
			return (NULL);
		}
		if (new == NULL)
			new = node;
		else
			last->next = node;
		last = node;
		lst = lst->next;
	}
	return (new);
}
