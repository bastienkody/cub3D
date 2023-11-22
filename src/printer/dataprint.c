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
	ft_fprintf(1, "------------------------------------\n");
	ft_fprintf(1, "PRINT_INFO:\n");
	ft_fprintf(1, "nopath:%s\n", info->no_path);
	ft_fprintf(1, "sopath:%s\n", info->so_path);
	ft_fprintf(1, "wepath:%s\n", info->we_path);
	ft_fprintf(1, "eapath:%s\n", info->ea_path);
	ft_fprintf(1, "Floor color : ");
	ft_fprintf(1, "%x", info->floor_rgb);
	ft_fprintf(1, "\nCeiling color : ");
	ft_fprintf(1, "%x", info->ceil_rgb);
	ft_fprintf(1, "\n");
	i = -1;
	ft_fprintf(1, "Map:\n");
	while (info->map && info->map[++i])
		ft_fprintf(1, "%s\n", info->map[i]);
	ft_fprintf(1, "Player pos = x:%i, y:%i\n", info->pposx, info->pposy);
	ft_fprintf(1, "Player dir = x:%i, y:%i\n", info->pdirx, info->pdiry);
	ft_fprintf(1, "------------------------------------\n");
}
