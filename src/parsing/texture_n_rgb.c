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

/*	bitshifting is consistent to endianess (maths, not data representation)	*/
unsigned int	argb_to_hex(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

/*	because of use ft_split on comma ...	*/
int	count_c_in_str(char *str, char c)
{
	int	nb;

	nb = 0;
	while (str && *str)
		if (c == *str++)
			nb++;
	return (nb);
}

int	check_rgb(t_info *info, char **rgb_split, char *line, char **line_split)
{
	int	i;
	int	j;
	int rgb_tmp[3];

	if (!rgb_split)
		return (print_error(ALLOC_FAIL, NULL), 0);
	if (count_c_in_str(line, ',') != 2 || tab_len(rgb_split) != 3)
		return (print_error(BAD_LINE, line), free_charray(rgb_split), 0);
	i = -1;
	while (++i < 3)
	{
		if (!ft_atouc_novf(rgb_split[i], rgb_tmp[i]))
			return (print_error(BAD_NBR, line), 0);
		j = -1;
		while (++j < 3)
			if (!ft_isdigit(rgb_split[i][j]))
				return (print_error(BAD_NBR, line), free_charray(rgb_split), 0);
	}
	if (*line_split[0] == 'F')
	{
		info->floor_rgb = argb_to_hex(255, rgb_tmp[0], rgb_tmp[1], rgb_tmp[2]);
		info->floor = true;
	}
	else
	{
		info->ceil_rgb = argb_to_hex(255, rgb_tmp[0], rgb_tmp[1], rgb_tmp[2]);
		info->ceil = true;
	}
	// store rgb needed bc of norminette?
	return (1);
}

int	get_rgb(char *line, char **split, t_info *info)
{
	char		*join;
	char		**rgb_split;

	if (tab_len(split) < 2)
		return (print_error(BAD_LINE, line), free_charray(split), free(line), 0);
	join = superjoin_tab_fall(split + 1);
	if (!join)
		return (print_error(ALLOC_FAIL, NULL), free(*split), free(split), free(line), 0);
	rgb_split = ft_split(join, ',');
	free(join);
	if (!check_rgb(info, rgb_split, line, split))
		return (free(*split), free(split), free(line), 0);
	free_charray(rgb_split);
	return (free(*split), free(split), free(line), 1);
}
