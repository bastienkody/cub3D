/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:21:13 by bguillau          #+#    #+#             */
/*   Updated: 2022/11/18 17:19:01 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (!new)
		return ;
	if (lst)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		ptr = ft_lstlast(*lst);
		ptr->next = new;
	}
}
