/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_n_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:53:45 by bguillau          #+#    #+#             */
/*   Updated: 2023/10/18 15:53:47 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	get_texture(char *line, char **split, t_data *data)
{
	int	fd;

	if (tab_len(split) != 2)
		return (print_error(BAD_LINE, line), free_char_matrix(split), 0);
	fd = open(split[1], O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Error\nImpossible to open texture path ");
		perror(split[1]);
	}
	if (!ft_strcmp(split[0], "NO"))
		data->no_path = fd;
	else if (!ft_strcmp(split[0], "SO"))
		data->so_path = fd;
	else if (!ft_strcmp(split[0], "WE"))
		data->we_path = fd;
	else if (!ft_strcmp(split[0], "EA"))
		data->ea_path = fd;
	return (free_char_matrix(split), fd);
}

int	check_rgb_split(char **rgb, char *line, t_data *data)
{
	int	i;
	int	j;

	if (!rgb)
		return (print_error(ALLOC_FAIL, NULL), 0);
	if (tab_len(rgb) != 3)
		return (print_error(BAD_LINE, line), 0);
	i = -1;
	while (rgb[++i])
	{
		j = 0;
		while (rgb[i][j])
			if (!ft_isdigit(rgb[i][j++]))
				return (print_error(BAD_LINE, line), free_char_matrix(rgb), 0);
	}
	return (1);
}

/*	atoc dans check_rgb?	*/
int	get_rgb(char *line, char **split, t_data *data)
{
	char		*join;
	char		**rgb_split;

	if (tab_len(split) < 2)
		return (print_error(BAD_LINE, line), free_char_matrix(split), 0);
	join = superjoin_tab_fall(split + 1); // split[0] + split a free later
	if (!join)
		return (print_error(ALLOC_FAIL, NULL), free(*split), free(split), 0);
	rgb_split = ft_split(join, ',');	// to be freed too
	if (!check_rgb_split(rgb_split, line, data))
		return (free(*split), free(split), 0);
	if (!ft_strcmp(split[0], "F"))
	{
		if (!ft_atoc_novf(rgb_split[0], data->floor_rgb[0]) || !ft_atoc_novf( \
			rgb_split[1], data->floor_rgb[1]) || !ft_atoc_novf(rgb_split[2], \
			data->floor_rgb[2]))
			return (print_error(BAD_LINE, line), free(*split), free(split), 0);
	}
	else
		if (!ft_atoc_novf(rgb_split[0], data->ceil_rgb[0]) || !ft_atoc_novf( \
			rgb_split[1], data->ceil_rgb[1]) || !ft_atoc_novf(rgb_split[2], \
			data->ceil_rgb[2]))
			return (print_error(BAD_LINE, line), free(*split), free(split), 0);
	return (free(*split), free(split), free_char_matrix(rgb_split), 1);
}
