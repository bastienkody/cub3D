/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:41:58 by bguillau          #+#    #+#             */
/*   Updated: 2023/10/16 15:42:38 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	print_info(t_info *info)
{
	int	i;

	if (!info)
		return ((void)ft_fprintf(1, "info addr is NULL\n"));
	ft_fprintf(1, "nopath:%i\n", info->no_path);
	ft_fprintf(1, "sopath:%i\n", info->so_path);
	ft_fprintf(1, "wepath:%i\n", info->we_path);
	ft_fprintf(1, "eapath:%i\n", info->ea_path);
	i = -1;
	ft_fprintf(1, "Floor color : ");
	while (++i < 3)
		ft_fprintf(1, "%i,", info->floor_rgb[i]);
	i = -1;
	ft_fprintf(1, "\nCeiling color : ");
	while (++i < 3)
		ft_fprintf(1, "%i,", info->ceil_rgb[i]);
	ft_fprintf(1, "\n");
	i = -1;
	ft_fprintf(1, "Map:\n");
	while (info->map && info->map[++i])
		ft_fprintf(1, "%s\n", info->map[i]);
}
