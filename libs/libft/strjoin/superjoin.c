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
#include <stdarg.h>

/*	join all va strings ; input must be NULL TERMINATED ! ; does not free
	if s1==null : return strdup("") ; malloc err : return NULL	*/
char	*superjoin(char const *s1, ...)
{
	va_list	ap;
	char	*ret;
	char	*new;

	if (!s1)
		return (ft_strdup(""));
	ret = ft_strdup(s1);
	va_start(ap, s1);
	new = (char *) va_arg(ap, char *);
	while (new)
	{
		ret = strjoin_f1(ret, new);
		if (!ret)
			return (NULL);
		new = (char *) va_arg(ap, char *);
	}
	va_end(ap);
	return (strjoin_char_fstr(ret, 0));
}

/*	free all va strings	*/
char	*superjoin_fall(char const *s1, ...)
{
	va_list	ap;
	char	*ret;
	char	*new;

	if (!s1)
		return (ft_strdup(""));
	ret = ft_strdup(s1);
	va_start(ap, s1);
	new = (char *) va_arg(ap, char *);
	while (new)
	{
		ret = strjoin_fall(ret, new);
		if (!ret)
			return (NULL);
		new = (char *) va_arg(ap, char *);
	}
	va_end(ap);
	free((char *)s1);
	return (strjoin_char_fstr(ret, 0));
}

/*	tab must be NULL terminated	*/
char	*superjoin_tab(char **tab)
{
	char	*ret;

	if (!tab)
		return (ft_strdup(""));
	ret = ft_strdup(*tab);
	while (++tab && *tab)
	{
		ret = strjoin_f1(ret, *tab);
		if (!ret)
			return (NULL);
	}
	return (strjoin_char_fstr(ret, 0));
}

/*	tab must be NULL terminated	*/
char	*superjoin_tab_fall(char **tab)
{
	char	*ret;

	if (!tab)
		return (ft_strdup(""));
	ret = ft_strdup(*tab);
	free(*tab);
	while (++tab && *tab)
	{
		ret = strjoin_fall(ret, *tab);
		if (!ret)
			return (NULL);
	}
	return (strjoin_char_fstr(ret, 0));
}
