/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:40:02 by bguillau          #+#    #+#             */
/*   Updated: 2022/11/21 11:28:58 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	int		i;
	int		new_len;

	if (!s)
		return (NULL);
	if (!len || !ft_strlen(s) || start > ft_strlen(s) - 1)
	{
		res = malloc(1 * sizeof(char));
		*res = '\0';
		return (res);
	}
	if (len > ft_strlen(s) - start)
		new_len = ft_strlen(s) - start;
	else
		new_len = len;
	res = malloc((new_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (s[++i + start] && len--)
		res[i] = s[i + start];
	res[i] = '\0';
	return (res);
}
