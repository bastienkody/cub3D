
#include "../../inc/cub3D.h"

int	is_edge(char **map, int i, int j)
{
	if (i == 0 || i == tab_len(map) - 1 || j == 0 || i == tab_len(map) - 1)
		return (1);
	// check pour lignes dont strlen(map[n]) > (map[n-1] || map[n+1]) -> must be wall or space?
	// if (! firstline !lastline)
		// if (j >= ft_strlen(map[i-1]) || j>= ft_strlen(map[i+1]))
			// return (1);
	return (0);
}

int	space_to_wall(char **map, int i, int j)
{
	if (map[i][j] == ' ')
		map[i][j] = '1';
	return (1);
}

// MAPCHAR = "NSEW01 "
int	map_checker(char **map)
{
	static			int	p_pos = 0;
	int				i;
	int				j;

	if (tab_len(map) < 3)
		return (print_error(ORDINATE, NULL), 0);
	i = -1;
	while(map[++i])
	{
		if (ft_strlen(map[i]) < 3)
			return (print_error(ABSCISSA, NULL), 0);
		j = -1;
		while(map[i][++j])
		{
			if (!ft_strchr(MAPCHAR, map[i][j]))
				return (print_error(BAD_MAP_CHAR, map[i]), 0);
			if (space_to_wall(map, i, j) && is_edge(map, i, j))
				if (!is_str_only(map[i], "1"))
					return (print_error(BAD_WALL, NULL), 0);
			if (ft_strchr(NSEW, map[i][j]))
				p_pos += 1;
		}
	}
	if (p_pos != 1)
		return (print_error(BAD_PPOS, map[i]), 0);
}