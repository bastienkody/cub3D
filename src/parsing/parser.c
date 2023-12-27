/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:22:51 by bguillau          #+#    #+#             */
/*   Updated: 2023/11/17 16:40:36 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	open_config_file(int argc, char **argv)
{
	int			fd;
	const char	*path = argv[1];

	if (argc != 2)
		return (print_error(BAD_ARG_NB, NULL), -1);
	path = argv[1];
	if (ft_strlen(path) < 5 || ft_strcmp(&path[ft_strlen(path) -4], ".cub"))
		return (print_error(BAD_CONFIG_NAME, NULL), -2);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Error\nImpossible to open ");
		perror(path);
	}
	return (fd);
}

int	is_config_full(t_parser *pars)
{
	if (pars->no_path && pars->so_path && pars->we_path && pars->ea_path)
		if (pars->ceil && pars->floor && tab_len(pars->map))
			return (1);
	return (0);
}

int	next_map_line(char *line, char **split, t_parser *pars)
{
	char	**new_map;

	free_charray(split);
	if (pars->map)
	{
		new_map = charray_add_one(pars->map, ft_strdup(line));
		pars->map = new_map;
		if (!pars->map)
			return (print_error(ALLOC_FAIL, NULL), free(line), 0);
	}
	else
	{
		pars->map = malloc(2 * sizeof(char *));
		if (!pars->map)
			return (print_error(ALLOC_FAIL, NULL), free(line), 0);
		pars->map[0] = ft_strdup(line);
		pars->map[1] = NULL;
	}
	free(line);
	return (1);
}

int	analyze_line(char *line, char **split, t_parser *pars)
{
	static int	map_on = 0;

	update_map_on(&map_on, pars);
	if (!split && !is_str_only(line, " "))
		return (print_error(ALLOC_FAIL, NULL), free(line), 0);
	if (!map_on)
	{
		if (is_texture_line(split))
			return ((get_texture(line, split, pars) > 0));
		if (is_rgb_line(split))
			return (get_rgb(line, split, pars));
	}
	if (map_on && ft_strlen(line))
		return (next_map_line(line, split, pars));
	if (map_on && tab_len(pars->map) && !ft_strlen(line))
		return (print_error(EMPTY, NULL), free_charray(split), free(line), 0);
	if (!is_str_only(line, " "))
		return (print_error(NOTCONF, line), free_charray(split), free(line), 0);
	return (free(line), free_charray(split), 1);
}

t_parser	*main_parser(int argc, char **av)
{
	t_parser	*pars;
	int			fd;
	char		*line;

	fd = open_config_file(argc, av);
	if (fd < 0)
		return (NULL);
	pars = ft_calloc(1, sizeof(t_info));
	if (!pars)
		return (print_error(ALLOC_FAIL, NULL), NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			line[ft_strlen(line) - 1] = '\0';
		if (!analyze_line(line, ft_split(line, ' '), pars))
			return (end_parser(pars), close(fd), NULL);
	}
	if (!is_config_full(pars))
		return (print_error(LACK_FO, av[1]), end_parser(pars), close(fd), NULL);
	return (close(fd), pars);
}
