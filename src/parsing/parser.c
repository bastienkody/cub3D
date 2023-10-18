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

int	open_config_file(char *path)
{
	int	fd;

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

// three steps: texture and rgb then map?
int	analyze_line(char *line, char **split, t_data *data)
{
	static int	map_on = 0;

	update_map_on(&map_on, data);
	if (!split && !is_str_only_c(line, ' '))
		return (print_error(ALLOC_FAIL, NULL), 0);
	if (!map_on)
	{
		if (is_texture_line(split))
			return ((get_texture(line, split, data) > 0));
		if (is_rgb_line(split))
			return (get_rgb(line, split, data));
	}
	if (map_on && !is_str_only_c(line, ' '))
		return (next_map_line(line, split, data));
	if (!is_str_only_c(line, ' '))
		return (print_error(LINE_NOT_CONFIG, line), 0);
	return (free(line), free_char_matrix(split), 1);
}

t_data	*main_parser(int argc, char **argv)
{
	t_data	*data;
	int		fd;
	char	*line;

	if (argc != 2)
		return (print_error(BAD_ARG_NB, NULL), NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error(ALLOC_FAIL, NULL), NULL);
	ft_bzero(data, sizeof(t_data));
	fd = open_config_file(argv[1]);
	if (fd < 0)
		return (NULL);
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (!analyze_line(line, ft_split(ft_strtrim(line, "\n"), ' '), data))
			return (free(line), NULL);
	}
	return (free(line), close(fd), data);
}
