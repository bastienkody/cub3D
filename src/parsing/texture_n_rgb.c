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

int	store_texture(int fd, char *id, t_info *info)
{
	if ((!ft_strcmp(id, "NO") && info->no_path) || (!ft_strcmp(id, "SO") && \
		info->so_path) || (!ft_strcmp(id, "WE") && info->we_path) || \
		(!ft_strcmp(id, "EA") && info->ea_path))
		return (print_error(MULTI_DEF, id), 0);
	if (!ft_strcmp(id, "NO") && !info->no_path)
		info->no_path = fd;
	else if (!ft_strcmp(id, "SO") && !info->so_path)
		info->so_path = fd;
	else if (!ft_strcmp(id, "WE") && !info->we_path)
		info->we_path = fd;
	else if (!ft_strcmp(id, "EA") && !info->ea_path)
		info->ea_path = fd;
	return (fd);
}

/*	is it fd or path needed for mlx_xpm_to_img??	*/
int	get_texture(char *line, char **split, t_info *info)
{
	int	fd;

	if (tab_len(split) != 2)
		return (print_error(BADLINE, line), free_charray(split), free(line), 0);
	fd = open(split[1], O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Error\nImpossible to open texture path ");
		perror(split[1]);
	}
	//close (fd) [if path needed not fd]
	// info_path = split[1];
	fd = store_texture(fd, split[0], info);
	return (free_charray(split), free(line), fd);
}

/*	protected against redefinition of colors	*/
int	store_rgb(t_info *info, char **line_split, unsigned char rgb_tmp[3])
{
	if (*line_split[0] == 'F' && !info->floor)
	{
		info->floor_rgb = argb_hex(255, rgb_tmp[0], rgb_tmp[1], rgb_tmp[2]);
		info->floor = true;
	}
	else if (*line_split[0] == 'F' && info->floor)
		return (print_error(MULTI_DEF, line_split[0]), 0);
	if (*line_split[0] == 'C' && !info->ceil)
	{
		info->ceil_rgb = argb_hex(255, rgb_tmp[0], rgb_tmp[1], rgb_tmp[2]);
		info->ceil = true;
	}
	else if (*line_split[0] == 'C' && !info->ceil)
		return (print_error(MULTI_DEF, line_split[0]), 0);
	return (1);
}

int	check_rgb(t_info *info, char **rgb_split, char *line, char **line_split)
{
	int				i;
	int				j;
	unsigned char	rgb_tmp[3];

	if (!rgb_split)
		return (print_error(ALLOC_FAIL, NULL), 0);
	if (count_c_in_str(line, ',') != 2 || tab_len(rgb_split) != 3)
		return (print_error(BADLINE, line), free_charray(rgb_split), 0);
	i = -1;
	while (++i < 3)
	{
		if (!ft_atouc_novf(rgb_split[i], &rgb_tmp[i]))
			return (print_error(BAD_NBR, line), free_charray(rgb_split), 0);
		j = -1;
		while (++j < 3 && rgb_split[i][j])
			if (!ft_isdigit(rgb_split[i][j]))
				return (print_error(BAD_NBR, line), free_charray(rgb_split), 0);
	}
	if (!store_rgb(info, line_split, rgb_tmp))
		return (free_charray(rgb_split), 0);
	return (1);
}

int	get_rgb(char *line, char **split, t_info *info)
{
	char		*join;
	char		**rgb_split;

	if (tab_len(split) < 2)
		return (print_error(BADLINE, line), free_charray(split), free(line), 0);
	join = superjoin_tab_fall(split + 1);
	if (!join)
		return (print_error(ALLOC_FAIL, NULL), free_charray(split), \
		free(line), 0);
	rgb_split = ft_split(join, ',');
	free(join);
	if (!check_rgb(info, rgb_split, line, split))
		return (free(*split), free(split), free(line), 0);
	free_charray(rgb_split);
	return (free(*split), free(split), free(line), 1);
}
