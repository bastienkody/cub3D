/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maximap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:26:12 by bguillau          #+#    #+#             */
/*   Updated: 2023/12/29 13:26:15 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/*	on maximap, left clic to teleport. out of range err handled	*/
void	maximap_teleport(int but, unsigned int x, unsigned int y, t_info *info)
{
	const double	xb = info->mmap_bordx / 2 + 1;
	const double	yb = info->mmap_bordy / 2 + 1;
	const double	newx = (x - xb) / info->mmap_tile_s;
	const double	newy = (y - yb) / info->mmap_tile_s;

	if (but != 1)
		return ;
	if (newx >= 0 && newx < info->mw && newy >= 0 && newy < info->mh)
	{
		if (info->map[(int)floor(newy)][(int)floor(newx)] != '0')
			return ((void)ft_fprintf(2, "%s%i,y%i%s\n", T_W, (int)floor(newx), (int)floor(newy), T_WB));
		info->posx = newx;
		info->posy = newy;
		maximap_display(info);
	}
}

/*	single tile size relative to map w/h + x/y borders	*/
void	get_maximap_size(t_info *info)
{
	const int	ylen = info->mh;
	const int	xlen = info->mw;
	const int	tiley = WIN_H / (ylen + 1);
	const int	tilex = WIN_W / (xlen + 1);

	info->mmap_tile_s = tilex;
	info->mmap_bordy = WIN_H - (tilex * ylen);
	info->mmap_bordx = WIN_W - (tilex * xlen);
	if (tiley < tilex)
	{
		info->mmap_tile_s = tiley;
		info->mmap_bordy = WIN_H - (tiley * ylen);
		info->mmap_bordx = WIN_W - (tiley * xlen);
	}
}

/*	used by mini and maxi maps
	for now :	player icon is a rect of size tile_s / 4
				if huuuuge map : just 1 pixel, no need to rect
				if huge map : no border (if not the red is almost unseen)
	upgrade with a circle + fov rays	*/
void	draw_player_icon(t_info *info, t_img *img_map, int tile_s)
{
	double	xpos = info->posx * tile_s;
	double	ypos = info->posy * tile_s;
	const int		size = tile_s / PLAYER_ICON_TO_MMAP_TILE_RATIO;

	if (xpos + size >= floor(info->posx) * tile_s + tile_s)
		xpos -= size;
	if (ypos + size >= floor(info->posy) * tile_s + tile_s)
		ypos -= size;
	if (size <= 1)
		pixel_w(img_map, (int)round(xpos), (int)round(ypos), RED);
	else if (size < 4)
		draw_rect(img_map, (int []){(int)round(xpos), \
		(int)round(ypos)}, (int []){size, size}, RED);
	else
		draw_rect_w_border(img_map, (int []){(int)round(xpos), \
		(int)round(ypos)}, (int []){size, size}, RED);
	//printf("x%f, y%f - (xm%f, ym%f)\n", info->posx, info->posy, xpos, ypos);
}

/*	only used once, by init. draw mmap floor/wall/void	*/
void	draw_first_maximap(t_info *info)
{
	int			y;
	int			x;
	const int	colorz[3] = {WHITE, GREY, BLACK};

	get_maximap_size(info);
	draw_rect(info->maximap, (int[]){0, 0}, (int[]){WIN_W, WIN_H}, BLACK);
	y = -1;
	while (++y * info->mmap_tile_s < WIN_H && info->map[y] != NULL)
	{
		x = -1;
		while (++x * info->mmap_tile_s < WIN_W && info->map[y][x] != '\0')
		{
			draw_rect_w_border(info->maximap, (int []){x * info->mmap_tile_s, \
			y * info->mmap_tile_s}, (int []){info->mmap_tile_s, \
			info->mmap_tile_s}, colorz[(int)info->map[y][x] - '0']);
		}
	}
}

/*	redraw (update ppos) + disp. can be separated in two functions	*/
void	maximap_display(t_info *info)
{
	static double	oldx = -1;
	static double	oldy = -1;
	const int		s = info->mmap_tile_s;
	const int		clr[3] = {WHITE, GREY, BLACK};

	if (!info->is_maximap)
		return ;
	if (oldx > -1 && oldy > -1 && (info->posx != oldx || info->posy != oldy))
		draw_rect_w_border(info->maximap, (int []){(int)floor(oldx) * s, \
		(int)floor(oldy) * s}, (int []){s, s}, \
		clr[info->map[(int)info->posy][(int)info->posx] - '0']);
	draw_player_icon(info, info->maximap, info->mmap_tile_s);
	oldx = info->posx;
	oldy = info->posy;
	mlx_put_image_to_window(info->ptr, info->win, info->bg_default->ptr, 0, 0);
	mlx_put_image_to_window(info->ptr, info->win, info->maximap->ptr, \
	(info->mmap_bordx / 2), (info->mmap_bordy / 2));
	draw_minimap(info);
}
