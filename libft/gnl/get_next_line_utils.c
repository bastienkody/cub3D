/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:13:53 by bguillau          #+#    #+#             */
/*   Updated: 2022/12/01 14:26:06 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	idx_of(char *buf, char c)
{
	int	i;

	i = -1;
	while (buf[++i])
	{
		if (buf[i] == c)
			return (i);
	}
	return (-1);
}

int	itrig(char *buf)
{
	int	i;

	i = 0;
	if (*buf != -1)
		return (i);
	while (buf[i] == TRIG)
		i++;
	return (i);
}

int	strle(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*strj(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	res = malloc((strle(s1) + strle(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		res[++j] = s1[i];
	i = -1;
	while (s2[++i])
		res[++j] = s2[i];
	res[++j] = '\0';
	free(s1);
	free(s2);
	return (res);
}

char	*subs(char *s, int start, int len)
{
	char	*res;
	int		i;
	int		new_len;

	if (!s)
		return (NULL);
	if (len > strle(s) - start)
		new_len = strle(s) - start;
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
