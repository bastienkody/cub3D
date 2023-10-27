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

/*	is it fd or path needed for mlx_xpm_to_img??	*/
int	get_texture(char *line, char **split, t_info *info)
{
	int	fd;

	if (tab_len(split) != 2)
		return (print_error(BAD_LINE, line), free_charray(split), free(line), 0);
	fd = open(split[1], O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Error\nImpossible to open texture path ");
		perror(split[1]);
	}
	//close (fd) [if path needed not fd]
	// info_path = split[1];
	if (!ft_strcmp(split[0], "NO"))
		info->no_path = fd;
	else if (!ft_strcmp(split[0], "SO"))
		info->so_path = fd;
	else if (!ft_strcmp(split[0], "WE"))
		info->we_path = fd;
	else if (!ft_strcmp(split[0], "EA"))
		info->ea_path = fd;
	return (free_charray(split), free(line), fd);
}

int	store_rgb(char **rgb, char *line, t_info *info)
{
	int	i;

	i = -1;
	if (line[0] == 'F')
	{
		while (++i < 3)
			if (!ft_atouc_novf(rgb[i], &info->floor_rgb[i]))
				return (print_error(BAD_NBR, line), free_charray(rgb), 0);
		info->floor = true;
	}
	else
	{
		while (++i < 3)
			if (!ft_atouc_novf(rgb[i], &info->ceil_rgb[i]))
				return (print_error(BAD_NBR, line), free_charray(rgb), 0);
		info->ceil = true;
	}
	return (1);
}

int	nb_c_in_str(char *str, char c)
{
	int	nb;

	nb = 0;
	while (str && *str)
		if (c == *str++)
			nb++;
	return (nb);
}

int	check_rgb(char **rgb, char *line)
{
	int			i;
	int			j;
	const int	comma_nb = nb_c_in_str(line, ',');

	if (!rgb)
		return (print_error(ALLOC_FAIL, NULL), 0);
	if (comma_nb != 2 || tab_len(rgb) != 3)
		return (print_error(BAD_LINE, line), free_charray(rgb), 0);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3 && rgb[i][j])
			if (!ft_isdigit(rgb[i][j]))
				return (print_error(BAD_NBR, line), free_charray(rgb), 0);
	}
	return (1);
}

int	get_rgb(char *line, char **split, t_info *info)
{
	char		*join;
	char		**rgb_split;

	if (tab_len(split) < 2)
		return (print_error(BAD_LINE, line), free_charray(split), free(line), 0);
	join = superjoin_tab_fall(split + 1); // split[0] + split a free later
	if (!join)
		return (print_error(ALLOC_FAIL, NULL), free(*split), free(split), free(line), 0);
	rgb_split = ft_split(join, ',');	// to be freed too
	free(join);
	if (!check_rgb(rgb_split, line) || !store_rgb(rgb_split, line, info))
		return (free(*split), free(split), free(line), 0);
	free_charray(rgb_split);
	return (free(*split), free(split), free(line), 1);
}
