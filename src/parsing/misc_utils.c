/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:52:46 by bguillau          #+#    #+#             */
/*   Updated: 2023/11/17 16:36:52 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/*	most significative bit at left for big endian (ret 1)	*/
int	get_endian(void)
{
	const int	nb = 1;

	if (*(char *)&nb == 1)
		return (0);
	else
		return (1);
}

/*	bitshifting is consistent to endianess (maths, not data representation)	*/
int	argb_hex(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

/*	because of use ft_split on comma ...	*/
int	count_c_in_str(char *str, char c)
{
	int	nb;

	nb = 0;
	while (str && *str)
		if (c == *str++)
			nb++;
	return (nb);
}

int	longest_line(char **map)
{
	int	l_line;
	int	i;

	l_line = 0;
	i = -1;
	while (map[++i])
		if ((int)ft_strlen(map[i]) > l_line)
			l_line = ft_strlen(map[i]);
	return (l_line);
}
