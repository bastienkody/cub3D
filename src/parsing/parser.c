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
		return (print_error(BAD_CONFIG_NAME), -2);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Impossible to open ");
		perror(path);
	}
	return (fd);
}

// failure for the map content (two steps: config then map?)
	// + tab_len needed
	// + is_str_only
int	analyze_line(char *line, char **split, t_data *data)
{
	if (!split)
		return (print_error(ALLOC_FAIL), 2);
	if (tab_len(split) < 2 && !is_str_only(line, ' '))
		return (ft_fprintf(2, "%s%s\n", BAD_LINE, line), 1);
	if (tab_len(split) == 2)
		config_line;
	else
		map_line;
}

t_data	*main_parser(int argc, char **argv)
{
	t_data	*data;
	int		fd;
	char	*line;

	if (argc != 2)
		return (print_error(BAD_ARG_NB), NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error(ALLOC_FAIL), NULL);
	ft_bzero(data, sizeof(t_data));
	fd = open_config_file(argv[1]);
	if (fd < 0)
		return (NULL);
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		// trim le linefeed
		if (analyze_line(line, ft_split(line, ' '), data) != 0)
			return (NULL);
	}
	return (data);
}
