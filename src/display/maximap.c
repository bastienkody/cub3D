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
	const unsigned int	xb = info->mmap_bordx / 2 + 1;
	const unsigned int	yb = info->mmap_bordy / 2 + 1;
	const int			newx = (x - xb) / info->mmap_tile_s;
	const int			newy = (y - yb) / info->mmap_tile_s;

	if (but != 1)
		return ;
	if (newx >= 0 && newx < (int)ft_strlen(*info->map) && newy >= 0 && \
		newy < tab_len(info->map))
	{
		if (info->map[newy][newx] != '0')
			return ((void)ft_fprintf(2, "%s%i,y%i%s\n", T_W, newx, newy, T_WB));
		info->pposx = newx;
		info->pposy = newy;
		info->pdirx = 0;
		info->pdiry = -1;
		ft_fprintf(1, "teleported in x%i, y%i\n", newx, newy);
		info->is_maximap = !info->is_maximap;	// keep on maximap display
		maximap_display(info);					// update maximap with newpos
	}
	else
		ft_fprintf(1, "%sx%i,y%i%s\n", T_OUT, newx, newy, T_OUTB);
}

/*	for now :	player icon is a rect of size tile_s / 4
				if huuuuge map : just 1 pixel, no need to rect
				if huge map : no border (if not the red is almost unseen)
	upgrade with a circle + fov rays
*/
void	draw_player_icon(t_info *info)
{
	const int	xpos = info->pposx * info->mmap_tile_s + info->mmap_tile_s / 2;
	const int	ypos = info->pposy * info->mmap_tile_s + info->mmap_tile_s / 2;
	const int	size = info->mmap_tile_s / PLAYER_ICON_TO_MMAP_TILE_RATIO;

	ft_fprintf(1, "size:%i\n", size);
	if (size <= 1)
		pixel_w(info->maximap, xpos, ypos, RED);
	else if (size < 4)
		draw_rect(info->maximap, (int[]){xpos - size / 2, ypos - size / 2}, \
		(int[]){size, size}, RED);
	else
		draw_rect_w_border(info->maximap, (int[]){xpos - size / 2, ypos - size \
		/ 2}, (int[]){size, size}, RED);
}

/*	need to be upgrading with precise angle	*/
void	maximap_display(t_info *info)
{
	int			y;
	int			x;
	const int	colorz[3] = {WHITE, GREY, BLACK};

	info->is_maximap = !info->is_maximap;
	if (!info->is_maximap)
		return ((void)mlx_put_image_to_window(info->ptr, info->win, \
		info->bg_default->ptr, 0, 0));
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
	draw_player_icon(info);
	mlx_put_image_to_window(info->ptr, info->win, info->maximap->ptr, \
	(info->mmap_bordx / 2), (info->mmap_bordy / 2));
}
