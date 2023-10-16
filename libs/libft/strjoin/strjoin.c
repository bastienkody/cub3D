/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:00:17 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/16 18:00:20 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*	join 2 strings, free s1	*/
char	*strjoin_f1(const char *s1, const char *s2)
{
	char	*ret;

	if (!s1 || !s2)
		return (free((void *)s1), NULL);
	ret = ft_strjoin(s1, s2);
	free((void *)s1);
	return (ret);
}

/*	join 2 strings, free s2	*/
char	*strjoin_f2(const char *s1, const char *s2)
{
	char	*ret;

	if (!s1 || !s2)
		return (free((void *)s2), NULL);
	ret = ft_strjoin(s1, s2);
	free((void *)s2);
	return (ret);
}

/*	join 2 strings, free all	*/
char	*strjoin_fall(const char *s1, const char *s2)
{
	char	*ret;

	if (!s1 || !s2)
		return (free((void *)s1), free((void *)s2), NULL);
	ret = ft_strjoin(s1, s2);
	free((void *)s1);
	free((void *)s2);
	return (ret);
}
