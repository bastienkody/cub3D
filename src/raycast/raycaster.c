/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:51:47 by bguillau          #+#    #+#             */
/*   Updated: 2024/01/03 17:51:49 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	post_dda_calculations(t_raycast *rc, t_info *info)
{
	// distance to wall
	rc->pwall = rc->sidex - rc->deltax;
	if (rc->side == 1)
		rc->pwall = rc->sidey - rc->deltay;
	if (rc->pwall == 0)
		rc->pwall = 1;
	rc->lineh = (int)(((double)WIN_H * 1.25) / rc->pwall);
	// start/end of texture drawings within line
	rc->start = -rc->lineh / 2 + WIN_H / 2 + PITCH;
	rc->end = rc->lineh / 2 + WIN_H / 2 + PITCH;
	if (rc->start < 0)
		rc->start = 0;
	if (rc->end >= WIN_H)
		rc->end = WIN_H ;
	// what texture ? change to nsew selection ?
	rc->whatext = info->map[rc->mapy][rc->mapx] - 1;
	// where on the texture exactly
	rc->wallx = info->posx + rc->pwall *rc->raydirx;
	if (rc->side == 0)
		rc->wallx = info->posy + rc->pwall * rc->raydiry;
	rc->wallx -= floor(rc->wallx); // nsp
	// texture x pos
	rc->xtext = (int)(rc->wallx * (double)TILE_S);
	if ((rc->side == 0 && rc->raydirx > 0) || (rc->side == 1 && rc->raydiry < 0))
		rc->xtext = TILE_S - rc->xtext - 1; // a creuser aussi
}

void draw_raycast(t_raycast *rc, t_info *info, int x)
{
	unsigned int	color; // color of the texture
	const double	step = (double)TILE_S / (double)rc->lineh;
	double			textpos;
	int				ytext;
	int				y;

	textpos = (double)(rc->start - PITCH - WIN_H / 2 + (double)rc->lineh / 2) * step;
	y = rc->start - 1;
	while (++y < rc->end)
	{
		ytext = (int)textpos & (TILE_S - 1); // nsp necessaire ?
		textpos += step;
		//printf("textel x%i, y%i (texpos%f) | ", rc->xtext, ytext, textpos);
		color = get_color(info->s_text, rc->xtext, ytext);
		//printf("pixelw x%i, y%i, color %x\n", x, y, color);
		pixel_w(info->rc, x, y, color);
	}
	draw_vert_line(info->rc, x, (int []){0, rc->start}, info->ceil);
	draw_vert_line(info->rc, x, (int []){rc->end, WIN_H}, info->floor);
}

int	raycast_launcher(t_info *info)
{
	t_raycast	rc;
	int			x;
	double		camerax;

	draw_rect(info->rc, (int []){0, 0}, (int []){WIN_W, WIN_H}, WHITE);
	ft_bzero(&rc, sizeof(t_raycast));
	x = -1;
	while (++x < WIN_W)
	{
		camerax = 2 * x / (double)WIN_W - 1;
		rc.mapx = (int)info->posx;
		rc.mapy = (int)info->posy;
		rc.raydirx = info->dirx + info->planex * camerax;
		rc.raydiry = info->diry + info->planey * camerax;
		dda_prep(&rc, info->posx, info->posy);
		dda(&rc, info->map);
		post_dda_calculations(&rc, info);
		printf("x:%i (xcam%f), lih:%i (start%i end%i) ", x, camerax, rc.lineh, rc.start, rc.end);
		print_rc(&rc);
		draw_raycast(&rc, info, x);
	}
	mlx_put_image_to_window(info->ptr, info->win, info->rc->ptr, 0, 0);
	return (1);
}

