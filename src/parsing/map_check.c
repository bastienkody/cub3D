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
	const int	x_len = ft_strlen(map[i]);
	const int	y_len = tab_len(map);

	if (i == 0 || i == y_len - 1 || j == 0 || j == x_len - 1)
		if (map[i][j] != '1' && map[i][j] != '2')
			return (print_error(BAD_WALL, NULL), 0);
	if (map[i][j] == '2')
	{
		if (i > 0 && map[i - 1][j] == '0')
			return (print_error(BAD_SPACE, map[i]), 0);
		if (i < y_len - 1 && map[i + 1][j] == '0')
			return (print_error(BAD_SPACE, map[i]), 0);
		if (j > 0 && map[i][j - 1] == '0')
			return (print_error(BAD_SPACE, map[i]), 0);
		if (j < x_len - 1 && map[i][j + 1] == '0')
			return (print_error(BAD_SPACE, map[i]), 0);
	}
	return (1);
}

/*	resize all lines to the longest	found in map
	turn spaces and extended size chars to '2'	*/
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
				map[i][j] = '2';
		map[i][j] = '\0';
	}
	return (1);
}

void	store_p_pos(t_parser *pars)
{
	int	i;
	int	j;

	i = -1;
	while (pars->map[++i])
	{
		j = -1;
		while (pars->map[i][++j])
		{
			if (ft_strchr(NSEW, pars->map[i][j]))
			{
				pars->pposx = (double)j;
				pars->pposy = (double)i;
				if (pars->map[i][j] == 'N')
				{
					pars->pdiry = -1;
					pars->planex = PLANE_ANG_TO_DIR;
				}
				if (pars->map[i][j] == 'S')
				{
					pars->pdiry = 1;
					pars->planex = -PLANE_ANG_TO_DIR;
				}
				if (pars->map[i][j] == 'W')
				{
					pars->pdirx = -1;
					pars->planey = -PLANE_ANG_TO_DIR;
				}
				if (pars->map[i][j] == 'E')
				{
					pars->pdirx = 1;
					pars->planey = PLANE_ANG_TO_DIR;
				}
				pars->map[i][j] = '0';
			}
		}
	}
}

int	check_bad_char_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		if (!is_str_only(map[i], MAPCHAR))
			return (print_error(BAD_MAP_CHAR, map[i]), 0);
	return (1);
}

int	map_checker(t_parser *pars)
{
	static int	p_pos = 0;
	int			i;
	int			j;

	if (!check_bad_char_map(pars->map) || !normalize_map(pars->map))
		return (0);
	if (tab_len(pars->map) < 3 || ft_strlen(pars->map[0]) < 3)
		return (print_error(TOO_SMALL, NULL), 0);
	i = -1;
	while (pars->map[++i])
	{
		j = -1;
		while (pars->map[i][++j])
		{
			if (!is_this_edge_a_wall(pars->map, i, j))
				return (0);
			if (ft_strchr(NSEW, pars->map[i][j]))
				p_pos += 1;
		}
	}
	if (p_pos != 1)
		return (print_error(BAD_PPOS, pars->map[i]), 0);
	return (store_p_pos(pars), 1);
}
