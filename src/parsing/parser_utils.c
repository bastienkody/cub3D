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
	while (tab && *tab++)
		i++;
	return (i);
}

int	is_str_only(char *str, char *valid)
{
	if (!valid)
		return (1);
	while (*str)
		if (!ft_strchr(valid, *str++))
			return (0);
	return (1);
}

int	is_texture_line(char **split)
{
	int					i;
	static const char	*start[5] = {"NO", "SO", "WE", "EA", NULL};

	if (!split || !split[0])
		return (0);
	i = -1;
	while (++i < 4)
		if (!ft_strcmp(split[0], start[i]))
			return (1);
	return (0);
}

int	is_rgb_line(char **split)
{
	int					i;
	static const char	*start[3] = {"F", "C", NULL};

	if (!split || !split[0])
		return (0);
	i = -1;
	while (++i < 2)
		if (!ft_strcmp(split[0], start[i]))
			return (1);
	return (0);
}

/*	set map_on when config infos are all done	*/
void	update_map_on(int *map_on, t_info *info)
{
	if (!(*map_on) && info->no_path && info->so_path && info->we_path \
		&& info->ea_path && info->floor && info->ceil)
		*map_on = 1;
}
