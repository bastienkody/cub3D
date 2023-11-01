/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:22:51 by bguillau          #+#    #+#             */
/*   Updated: 2023/10/13 16:23:21 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	open_config_file(int argc, char **argv)
{
	int		fd;
	char	*path;

	if (argc != 2)
		return (print_error(BAD_ARG_NB, NULL), 0);
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

int	is_config_full(t_info *info)
{
	if (info->no_path && info->so_path && info->we_path && info->ea_path)
		if (info->ceil && info->floor && tab_len(info->map))
			return (1);
	return (0);
}

int	next_map_line(char *line, char **split, t_info *info)
{
	char	**new_map;

	free_charray(split);
	if (info->map)
	{
		new_map = charray_add_one(info->map, ft_strdup(line));
		info->map = new_map;
		if (!info->map)
			return (print_error(ALLOC_FAIL, NULL), free(line), 0);
	}
	else
	{
		info->map = malloc(2 * sizeof(char *));
		if (!info->map)
			return (print_error(ALLOC_FAIL, NULL), free(line), 0);
		info->map[0] = ft_strdup(line);
		info->map[1] = NULL;
	}
	free(line);
	return (1);
}

int	analyze_line(char *line, char **split, t_info *info)
{
	static int	map_on = 0;

	update_map_on(&map_on, info);
	if (!split && !is_str_only(line, " "))
		return (print_error(ALLOC_FAIL, NULL), free(line), 0);
	if (!map_on)
	{
		if (is_texture_line(split))
			return ((get_texture(line, split, info) > 0));
		if (is_rgb_line(split))
			return (get_rgb(line, split, info));
	}
	if (map_on && ft_strlen(line))
		return (next_map_line(line, split, info));
	if (map_on && tab_len(info->map) && !ft_strlen(line))
		return (print_error(EMPTY, NULL), free_charray(split), free(line), 0);
	if (!is_str_only(line, " "))
		return (print_error(NOTCONF, line), free_charray(split), free(line), 0);
	return (free(line), free_charray(split), 1);
}

t_info	*main_parser(int argc, char **av)
{
	t_info	*info;
	int		fd;
	char	*line;

	fd = open_config_file(argc, av);
	if (fd < 0)
		return (NULL);
	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		return (print_error(ALLOC_FAIL, NULL), NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			line[ft_strlen(line) - 1] = '\0';
		if (!analyze_line(line, ft_split(line, ' '), info))
			return (end_free(info), close(fd), NULL);
	}
	if (!is_config_full(info))
		return (print_error(LACK_INFO, av[1]), end_free(info), close(fd), NULL);
	return (close(fd), info);
}
