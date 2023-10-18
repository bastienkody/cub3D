/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:03:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/10/18 12:03:04 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/*	size (entries nb) of a char**	*/
int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while(tab && *tab++)
		i++;
	return (i);
}

int	is_str_only_c(char *str, char c)
{
	while(*str)
		if (*str++ != c)
			return (0);
	return (1);
}

int	is_texture_line(char **split)
{
	int					i;
	static const char	*start[5] = {"NO", "SO", "WE", "EA", NULL};

	i = -1;
	while(++i < 4)
		if (!ft_strcmp(split[0], start[i]))
			return (1);
	return (0);
}

int	is_rgb_line(char **split)
{
	int					i;
	static const char	*start[3] = {"F", "C", NULL};

	i = -1;
	while(++i < 2)
		if (!ft_strcmp(split[0], start[i]))
			return (1);
	return (0);
}

/*	set map_on when config infos are all done	*/
void	update_map_on(int *map_on, t_data *data)
{
	if (!(*map_on) && data->no_path && data->so_path && data->we_path &&\
		data->ea_path && data->floor_rgb && data->ceil_rgb)
		*map_on = 1;
}
