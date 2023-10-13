/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:18:09 by bguillau          #+#    #+#             */
/*   Updated: 2022/11/21 11:28:49 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_charset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i++])
			return (1);
	}
	return (0);
}

static void	count_ards(size_t *fw, size_t *bw, char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && is_charset(s1[i], set))
	{
		*fw += 1;
		i++;
	}
	i = ft_strlen(s1) -1;
	while (i >= 0 && is_charset(s1[i--], set))
		*bw += 1;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	i;
	size_t	backw;
	size_t	forw;

	if (!s1 || !set)
		return (NULL);
	forw = 0;
	backw = 0;
	count_ards(&forw, &backw, s1, set);
	if (backw + forw < ft_strlen(s1))
		res = malloc((ft_strlen(s1) - backw - forw + 1) * sizeof(char));
	else
		res = malloc(1 * sizeof(char));
	if (!res)
		return (NULL);
	i = forw;
	while (i < ft_strlen(s1) - backw)
		*res++ = s1[i++];
	*res = '\0';
	if (backw + forw < ft_strlen(s1))
		return (res - ft_strlen(s1) + backw + forw);
	else
		return (res);
}
