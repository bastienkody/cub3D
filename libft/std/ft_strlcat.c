/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:07:30 by bguillau          #+#    #+#             */
/*   Updated: 2022/11/18 12:54:04 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dest[i] && i < size)
	{
		i++;
		j++;
	}
	k = 0;
	while (i < size - 1 && src[k] != '\0')
		dest[i++] = src[k++];
	if (j < size)
		dest[i] = '\0';
	return (j + ft_strlen(src));
}
