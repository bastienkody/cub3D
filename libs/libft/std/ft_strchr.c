/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:56:22 by bguillau          #+#    #+#             */
/*   Updated: 2022/11/18 18:26:36 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	slen;
	char	*s_tmp;

	if (!s)
		return (NULL);
	slen = ft_strlen(s) + 1;
	s_tmp = (char *) s;
	c = (char) c;
	while (slen--)
	{
		if (*s_tmp == c)
			return (s_tmp);
		s_tmp++;
	}
	return (NULL);
}
