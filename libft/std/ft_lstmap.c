/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:41:03 by bguillau          #+#    #+#             */
/*   Updated: 2022/11/18 18:16:18 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*start;

	if (!lst || !f || !del)
		return (NULL);
	start = ft_lstnew((f)(lst->content));
	if (!start)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstnew((f)(lst->content));
		if (!tmp)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		ft_lstadd_back(&start, tmp);
		lst = lst->next;
	}
	return (start);
}
