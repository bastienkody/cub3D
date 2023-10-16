/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:59:40 by bguillau          #+#    #+#             */
/*   Updated: 2022/11/21 11:25:38 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_wd(char const *s, char c)
{
	int	i;
	int	j;
	int	nb;

	nb = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		while (s[i] && s[i] != c)
		{
			j++;
			i++;
		}
		if (j)
			nb += 1;
	}
	return (nb);
}

static char	*gen_wd(const char *s, char c, int *i)
{
	int		j;
	char	*res;

	j = 0;
	while (s[*i] && s[*i] == c)
		*i += 1;
	while (s[*i] && s[*i] != c)
	{
		j++;
		*i += 1;
	}
	res = malloc((j + 1) * sizeof(char));
	if (!res)
		return (NULL);
	*i -= j;
	while (s[*i] && s[*i] != c)
	{
		*res++ = s[*i];
		*i += 1;
	}
	*res = '\0';
	return (res - j);
}

static void	free_all(char **res, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(res[i++]);
	free(res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	res = malloc((count_wd(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < count_wd(s, c))
	{
		res[j] = gen_wd(s, c, &i);
		if (!res[j++])
		{
			free_all(res, j);
			return (NULL);
		}
	}
	res[j] = NULL;
	return (res);
}
