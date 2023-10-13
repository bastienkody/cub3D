/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:30:00 by bguillau          #+#    #+#             */
/*   Updated: 2022/11/22 14:47:04 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	n;
	size_t	i;

	if (!big || !little)
		return (NULL);
	if (!ft_strlen(little))
		return ((char *) big);
	n = 0;
	while (big[n] && n < len)
	{
		if (big[n] == *little)
		{
			i = 0;
			while (big[n + i] && big[n + i] == little[i] && n + i < len)
				i++;
			if (i == ft_strlen(little))
				return ((char *) &big[n]);
		}
		n++;
	}
	return (NULL);
}
