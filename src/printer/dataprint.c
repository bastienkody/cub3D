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

void	print_is(t_info *info)
{
	ft_fprintf(1, "is_intro\t: %i\n", info->is_intro);
	ft_fprintf(1, "is_outro\t: %i\n", info->is_outro);
	ft_fprintf(1, "is_maximap\t: %i\n", info->is_maximap);
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
	printf("Player pos\t: x=%f, y=%f\n", info->posx, info->posy);
	printf("Player dir\t: x=%f, y=%f\n", info->dirx, info->diry);
	printf("Player plane\t: x=%f, y=%f\n", info->planex, info->planey);
	print_map(info);
	print_is(info);
	ft_fprintf(1, "------------------------------------\n");
}

void	print_raycast(t_raycast *rc)
{
	ft_fprintf(1, "------------------------------------\n");
	ft_fprintf(1, "\t\033[1mPRINT_RAYCAST\033[m\n");
	ft_fprintf(1, "mapx:%i, mapy:%i\n", rc->mapx, rc->mapy);
	printf("raydirx:%f, raydiry:%f\n", rc->raydirx, rc->raydiry);
	ft_fprintf(1, "stepx:%i, stepy:%i\n", rc->stepx, rc->stepy);
	printf("deltax:%f, deltay:%f\n", rc->deltax, rc->deltay);
	printf("sidex:%f, sidey:%f\n", rc->sidex, rc->sidey);
	ft_fprintf(1, "side:%i\n", rc->side);
	printf("pwall:%f\n", rc->pwall);
	ft_fprintf(1, "lineh:%i, start%i, end%i\n", rc->lineh, rc->start, rc->end);
	printf("wallx%f, xtext%i\n", rc->wallx, rc->xtext);
	ft_fprintf(1, "------------------------------------\n");
}

void	print_rc(t_raycast *rc)
{
	printf("ray:x:%.2f, y:%.2f | delta:x%.2f,y:%.2f | side:x%.2f,y:%.2f | \
pwall:%.3f\n", rc->raydirx, rc->raydiry, rc->deltax, rc->deltay, \
	rc->sidex, rc->sidey, rc->pwall);
}
