/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:53:00 by bguillau          #+#    #+#             */
/*   Updated: 2023/11/01 17:53:06 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	is_this_edge_a_wall(char **map, int i, int j)
{
	const int	l_len = ft_strlen(map[i]);

	if (i == 0 || i == tab_len(map) - 1 || j == 0 || j == l_len - 1)
		if (map[i][j] != '1')
			return (0);
	return (1);
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

/*	resize all lines to the longest	found in map
	turn spaces and extended size chars to walls	*/
int	normalize_map(char **map)
{
	int			i;
	int			j;
	int			c_line;
	const int	l_line = longest_line(map);

	i = -1;
	while (map[++i])
	{
		c_line = ft_strlen(map[i]);
		if (c_line < l_line)
		{
			map[i] = ft_realloc(map[i], l_line + 1);
			if (!map[i])
				return (print_error(ALLOC_FAIL, NULL), 0);
		}
		j = -1;
		while (++j < l_line)
			if (j >= c_line || map[i][j] == ' ')
				map[i][j] = '1';
		map[i][j] = '\0';
	}
	return (1);
}

void	store_p_pos(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (info->map[++i])
	{
		j = -1;
		while (info->map[i][++j])
		{
			if (ft_strchr(NSEW, info->map[i][j]))
			{
				info->pposx = j;
				info->pposy = i;
				if (info->map[i][j] == 'N')
					info->pdiry = -1;
				if (info->map[i][j] == 'S')
					info->pdiry = 1;
				if (info->map[i][j] == 'W')
					info->pdirx = -1;
				if (info->map[i][j] == 'E')
					info->pdirx = 1;
				info->map[i][j] = '0';
			}
		}
	}
}

int	map_checker(t_info *info)
{
	static int	p_pos = 0;
	int			i;
	int			j;

	if (!normalize_map(info->map))
		return (0);
	if (tab_len(info->map) < 3 || ft_strlen(info->map[0]) < 3)
		return (print_error(TOO_SMALL, NULL), 0);
	i = -1;
	while (info->map[++i])
	{
		if (!is_str_only(info->map[i], MAPCHAR))
			return (print_error(BAD_MAP_CHAR, info->map[i]), 0);
		j = -1;
		while (info->map[i][++j])
		{
			if (!is_this_edge_a_wall(info->map, i, j))
				return (print_error(BAD_WALL, NULL), 0);
			if (ft_strchr(NSEW, info->map[i][j]))
				p_pos += 1;
		}
	}
	if (p_pos != 1)
		return (print_error(BAD_PPOS, info->map[i]), 0);
	return (store_p_pos(info), 1);
}
