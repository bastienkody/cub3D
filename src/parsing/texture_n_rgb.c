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

/*	convert/store rgb_tmp into hexa	
	use of an external converter? 
	if so maybe this function can be absorb by check_rgb ?	*/
/*int	store_rgb(char **rgb, char *line, t_info *info)
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

int	check_rgb(char **rgb_split, char *line, int rgb_tmp[3])
{
	int			i;
	int			j;

	if (!rgb_split)
		return (print_error(ALLOC_FAIL, NULL), 0);
	if (nb_c_in_str(line, ',') != 2 || tab_len(rgb_split) != 3)
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
	//if *line == 'F' then rgb_tmp into info->f_clr
	//if *line == 'C' then rgb_tmp into info->c_clr
	return (1);
}
*/
int	get_rgb(char *line, char **split, t_info *info)
{
	return ((void)line, (void)split, (void)info, 1);
}
/*	char		*join;
	char		**rgb_split;
	int			rgb_tmp[3];

	if (tab_len(split) < 2)
		return (print_error(BAD_LINE, line), free_charray(split), free(line), 0);
	join = superjoin_tab_fall(split + 1);
	if (!join)
		return (print_error(ALLOC_FAIL, NULL), free(*split), free(split), free(line), 0);
	rgb_split = ft_split(join, ',');
	free(join);
	if (!check_rgb(rgb_split, line, rgb_tmp) || !store_rgb(rgb_tmp, line, info))
		return (free(*split), free(split), free(line), 0);
	free_charray(rgb_split);
	return (free(*split), free(split), free(line), 1);
}*/
