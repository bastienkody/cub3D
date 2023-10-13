/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:06:17 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/22 19:06:19 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new;

	if (!ptr)
		return (malloc(size));
	new = malloc(size);
	if (!new)
		return (NULL);
	ft_memcpy(new, ptr, ft_strlen(ptr));
	free(ptr);
	return (new);
}
