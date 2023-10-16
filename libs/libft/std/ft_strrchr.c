/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:56:22 by bguillau          #+#    #+#             */
/*   Updated: 2022/11/18 18:46:29 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			slen;
	char			*s_tmp;

	if (!s)
		return (NULL);
	slen = ft_strlen(s) + 1;
	s_tmp = (char *) s + slen - 1;
	c = (char) c;
	while (slen--)
	{
		if (*s_tmp == c)
			return (s_tmp);
		s_tmp--;
	}
	return (NULL);
}
