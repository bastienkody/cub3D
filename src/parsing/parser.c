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

int	analyze_line(char *line, t_data *data)
{
	char	*buf;

	while (*line && *line != ' ')
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
		return (NULL);
	ft_bzero(data, sizeof(t_data));
	fd = open_config_file(argv[1]);
	if (fd < 0)
		return (NULL);
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (!analyze_line(line, data))
			return (0);
	}
	return (data);
}
