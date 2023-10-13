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

/*	join 3 str ; null input protected ; malloc error handled in ft_strjoin	*/

char	*strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*tmp;
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	return (free((void *)tmp), ret);
}

char	*strjoin3_f1(char const *s1, char const *s2, char const *s3)
{
	char	*tmp;
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (free((void *)s1), NULL);
	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	free((void *)s1);
	return (free((void *)tmp), ret);
}

char	*strjoin3_f2(char const *s1, char const *s2, char const *s3)
{
	char	*tmp;
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (free((void *)s2), NULL);
	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	free((void *)s2);
	return (free((void *)tmp), ret);
}

char	*strjoin3_f3(char const *s1, char const *s2, char const *s3)
{
	char	*tmp;
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (free((void *)s3), NULL);
	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	free((void *)s3);
	return (free((void *)tmp), ret);
}

char	*strjoin3_fall(char const *s1, char const *s2, char const *s3)
{
	char	*tmp;
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (free((void *)s1), free((void *)s2), free((void *)s3), NULL);
	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	free((void *)s1);
	free((void *)s2);
	free((void *)s3);
	return (free((void *)tmp), ret);
}
