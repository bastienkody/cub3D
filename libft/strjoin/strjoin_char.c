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

/*	append a signle char to the end of str
	str==NULL -> returns "c"
	str is malloced -> init str is freed
	str is stacked -> error	*/
char	*strjoin_char_fstr(char *str, char c)
{
	int	str_len;

	if (!str)
	{
		str_len = 0;
		str = malloc(2 * sizeof(char));
		if (!str)
			return (NULL);
	}
	else
	{
		str_len = ft_strlen(str);
		str = ft_realloc(str, (str_len + 1 + 1) * sizeof(char));
		if (!str)
			return (NULL);
	}
	str[str_len + 1] = '\0';
	str[str_len] = c;
	return (str);
}

/*	does not free str. unprotected against strdup malloc	*/
char	*strjoin_char(char *str, char c)
{
	int	str_len;

	str = ft_strdup(str);
	if (!str)
	{
		str_len = 0;
		str = malloc(2 * sizeof(char));
		if (!str)
			return (NULL);
	}
	else
	{
		str_len = ft_strlen(str);
		str = ft_realloc(str, (str_len + 1 + 1) * sizeof(char));
		if (!str)
			return (NULL);
	}
	str[str_len + 1] = '\0';
	str[str_len] = c;
	return (str);
}
