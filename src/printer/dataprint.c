/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:27:56 by bguillau          #+#    #+#             */
/*   Updated: 2023/12/29 13:27:58 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	print_map(t_info *info)
{
	int			i;
	const int	w = ft_strlen(*info->map);
	const int	h = tab_len(info->map);

	ft_fprintf(1, "Maximap:\n");
	ft_fprintf(1, "tilesize\t: %i\n", info->mmap_tile_s);
	ft_fprintf(1, "bordx\t\t: %i\n", info->mmap_bordx);
	ft_fprintf(1, "bordy\t\t: %i\n", info->mmap_bordy);
	i = -1;
	ft_fprintf(1, "Map:\n");
	ft_fprintf(1, "width\t\t: %i\nheight\t\t: %i\n", w, h);
	while (info->map && info->map[++i])
		ft_fprintf(1, "%s\n", info->map[i]);
}



void	print_info(t_info *info)
{
	static int	x;
	static int	y;

	mlx_get_screen_size(info->ptr, &x, &y);
	if (!info)
		return ((void)ft_fprintf(1, "info addr is NULL\n"));
	ft_fprintf(1, "------------------------------------\n");
	ft_fprintf(1, "\t\033[1mPRINT_INFO\033[m\n");
	ft_fprintf(1, "Screen size x%i, y%i", x, y);
	ft_fprintf(1, "floor color\t: %x\n", info->floor);
	ft_fprintf(1, "ceiling color\t: %x\n", info->ceil);
	ft_fprintf(1, "Player pos\t: x=%i, y=%i\n", info->pposx, info->pposy);
	ft_fprintf(1, "Player dir\t: x=%i, y=%i\n", info->pdirx, info->pdiry);
	print_map(info);
	ft_fprintf(1, "is_outro\t: =%i, y=%i\n", info->is_outro);
	ft_fprintf(1, "------------------------------------\n");
}
