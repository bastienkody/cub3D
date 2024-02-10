/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:51:47 by bguillau          #+#    #+#             */
/*   Updated: 2024/02/01 22:29:15 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	choose_texture(t_raycast *rc, t_info *info)
{
	if (rc->side == 0)
	{
		if (rc->raydirx < 0)
			rc->whatext = info->w_text;
		else
			rc->whatext = info->e_text;
	}
	else
	{
		if (rc->raydiry < 0)
			rc->whatext = info->n_text;
		else
			rc->whatext = info->s_text;
	}
}

void	post_dda_calculations(t_raycast *rc, t_info *info)
{
	rc->pwall = rc->sidex - rc->deltax;
	if (rc->side == 1)
		rc->pwall = rc->sidey - rc->deltay;
	if (rc->pwall == 0)
		rc->pwall = 1;
	rc->lineh = (int)(((double)WIN_H * 1.25) / rc->pwall);
	rc->start = -rc->lineh / 2 + WIN_H / 2;
	rc->end = rc->lineh / 2 + WIN_H / 2;
	if (rc->start < 0)
		rc->start = 0;
	if (rc->end >= WIN_H)
		rc->end = WIN_H ;
	choose_texture(rc, info);
	rc->wallx = info->posx + rc->pwall * rc->raydirx;
	if (rc->side == 0)
		rc->wallx = info->posy + rc->pwall * rc->raydiry;
	rc->wallx -= floor(rc->wallx);
	rc->xtext = (int)(rc->wallx * (double)rc->whatext->width);
	if ((!rc->side && rc->raydirx < 0) || (rc->side == 1 && rc->raydiry > 0))
		rc->xtext = rc->whatext->width - rc->xtext - 1;
}

void	draw_raycast(t_raycast *rc, t_info *info, int x)
{
	const double	step = (double)rc->whatext->height / (double)rc->lineh;
	double			textpos;
	int				ytext;
	int				y;

	textpos = (double)(rc->start - WIN_H / 2 + (double)rc->lineh / 2) * step;
	y = rc->start - 1;
	while (++y < rc->end)
	{
		ytext = (int)textpos;
		textpos += step;
		pixel_w(info->rc, x, y, get_color(rc->whatext, rc->xtext, ytext));
	}
	draw_vert_line(info->rc, x, (int []){0, rc->start}, info->ceil);
	draw_vert_line(info->rc, x, (int []){rc->end, WIN_H}, info->floor);
}

int	raycast_launcher(t_info *info)
{
	t_raycast	rc;
	int			x;
	double		camerax;

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
		draw_raycast(&rc, info, x);
	}
	draw_pistol(info);
	mlx_put_image_to_window(info->ptr, info->win, info->rc->ptr, 0, 0);
	draw_minimap(info);
	return (1);
}
