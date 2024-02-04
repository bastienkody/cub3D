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
	rc->wallx = info->posx + rc->pwall * rc->raydirx;
	if (rc->side == 0)
		rc->wallx = info->posy + rc->pwall * rc->raydiry;
	rc->wallx -= floor(rc->wallx); // nsp
	// texture x pos
	rc->xtext = (int)(rc->wallx * (double)TILE_S);
	if ((rc->side == 0 && rc->raydirx < 0) || (rc->side == 1 && rc->raydiry > 0))
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
	y = rc->start - 1 - info->crouch;
	while (++y < rc->end + info->crouch)
	{
		ytext = (int)textpos; // nsp necessaire ?
		textpos += step;
		//printf("textel x%i, y%i (texpos%f) | ", rc->xtext, ytext, textpos);
		color = get_color(info->s_text, rc->xtext, ytext);
		//printf("pixelw x%i, y%i, color %x\n", x, y, color);
		pixel_w(info->rc, x, y, color);
	}
	draw_vert_line(info->rc, x, (int []){0, rc->start - info->crouch}, info->ceil);
	if (rc->end - info->crouch < WIN_H)
	{
		//printf("rc->end - crouch:%i\n", rc->end - info->crouch);
		draw_vert_line(info->rc, x, (int []){rc->end - info->crouch, WIN_H}, info->floor);
	}
}

int	raycast_launcher(t_info *info)
{
	t_raycast	rc;
	int			x;
	double		camerax;

	draw_rect(info->rc, (int []){0, 0}, (int []){WIN_W, WIN_H}, WHITE); //no more white artefacts without this maybe needed tho ?
	ft_bzero(&rc, sizeof(t_raycast));
	x = -1;
	while (++x < WIN_W)
	{
		rc.ray = x;
		camerax = 2 * x / (double)WIN_W - 1;
		rc.mapx = (int)info->posx;
		rc.mapy = (int)info->posy;
		rc.raydirx = info->dirx + info->planex * camerax;
		rc.raydiry = info->diry + info->planey * camerax;
		dda_prep(&rc, info->posx, info->posy);
		dda(&rc, info->map);
		post_dda_calculations(&rc, info);
		//printf("x:%i (xcam%f), lih:%i (start%i end%i) ", x, camerax, rc.lineh, rc.start, rc.end);
		//print_rc(&rc);
		draw_raycast(&rc, info, x);
	}
	mlx_put_image_to_window(info->ptr, info->win, info->rc->ptr, 0, 0);
	return (1);
}

int	wall_found(t_info *info, int mp)
{
	int	col;
	int	line;

	line = mp / info->mw;
	col = mp % info->mw;
	if (info->map[line][col] == '1')
		return (fprintf(stderr, "FOUND WALL\n"), 1);
	return (0);
}

int	new_raycast(t_info *info)
{
	t_raycast	rc;
	int			rays;
	int		mx, my, mp, dof; float rayx, rayy, rayangle, xoffset, yoffset;

	rc.deltax = cos(info->angle) * 5;
	rc.deltay = sin(info->angle) * 5;
	rayangle = info->angle;
	ft_bzero(&rc, sizeof(t_raycast));
	rays = -1;
	while (++rays < 1)
	{
		//---Check Horizontal Lines---
		dof = 0; //depth of field
		float aTan = -1/tan(rayangle);
		if (rayangle > PI) //looking up
		{
			rayy = (((int)info->posy>>6)<<6) - 0.0001;
			rayx = (info->posy - rayy) * aTan + info->posx;
			yoffset = -64;
			xoffset = -yoffset * aTan;
		}
		if (rayangle < PI) //looking down
		{
			rayy = (((int)info->posy>>6)<<6) + 64;
			rayx = (info->posy - rayy) * aTan + info->posx;
			yoffset = 64;
			xoffset = -yoffset * aTan;
		}
		if (rayangle == 0 || rayangle == PI)
		{
			rayx = info->posx;
			rayy = info->posy;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int) (rayx)>>6;
			my = (int) (rayy)>>6;
			mp = my * info->mw + mx;
			fprintf(stderr, "mp %d\n", mp);
			if (mp < info->mw * info->mh && wall_found(info, mp) == 1)
				dof = 8;
			else
			{
				rayx += xoffset;
				rayy += yoffset;
				dof++;
			}
		}
		//---Check Vertical Lines---
		dof = 0; //depth of field
		float nTan = -tan(rayangle);
		if (rayangle > P2 && rayangle < P3) //looking left
		{
			rayx = (((int)info->posx>>6)<<6) - 0.0001;
			rayy = (info->posx - rayx) * nTan + info->posy;
			yoffset = -64;
			yoffset = xoffset * nTan;
		}
		if (rayangle < P2 || rayangle > P3) //looking right
		{
			rayx = (((int)info->posx>>6)<<6) + 64;
			rayy = (info->posx - rayx) * nTan + info->posy;
			xoffset = 64;
			yoffset = -xoffset * nTan;
		}
		if (rayangle == 0 || rayangle == PI)
		{
			rayx = info->posx;
			rayy = info->posy;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int) (rayx)>>6;
			my = (int) (rayy)>>6;
			mp = my * info->mw + mx;
			fprintf(stderr, "mp %d\n", mp);
			if (mp < info->mw * info->mh && wall_found(info, mp) == 1)
				dof = 8;
			else
			{
				rayx += xoffset;
				rayy += yoffset;
				dof++;
			}
		}
	}
	mlx_put_image_to_window(info->ptr, info->win, info->rc->ptr, 0, 0);
	return (1);
}

int	check_hit(t_info *info, t_raycast *rc)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (rc->side < rc->sidey)
		{
			rc->sidex += rc->deltax;
			rc->mapx += rc->stepx;
			rc->side = 0;
		}
		else
		{
			rc->sidey += rc->deltay;
			rc->mapy += rc->stepy;
			rc->side = 1;
		}
		if (info->map[rc->mapx][rc->mapy] == '1')
			hit = 1;
	}
	return (0);
}

int	line_height(t_raycast *rc)
{
	if (rc->side == 0)
		rc->pwall = rc->sidex - rc->deltax;
	else
		rc->pwall = rc->sidey - rc->deltay;
	rc->lineh = (int)(WIN_H / rc->pwall);

	rc->start = -rc->lineh / 2 + WIN_H / 2;
	if (rc->start < 0)
		rc->start = 0;
	rc->end = rc->lineh / 2 + WIN_H / 2;
	if (rc->end >= WIN_H)
		rc->end = WIN_H - 1;
	// rc->whatext = 
	return (0);
}
//
int	raycasting(t_info *info)
{
	t_raycast rc;
	int	x;
	double	time;
	double	oldTime;

	time = 0;
	oldTime = 0;
	x = -1;
	ft_bzero(&rc, sizeof(t_raycast));
	while (++x < WIN_W)
	{
		rc.camerax = 2 * x / (double)WIN_W - 1;
		rc.raydirx = info->dirx + info->planex * rc.camerax;
		rc.raydiry = info->diry + info->planey * rc.camerax;

		rc.mapx = (int)(info->posx);
		rc.mapy = (int)(info->posy);

		if (rc.raydirx == 0)
			rc.deltax = 1e30;
		else
			rc.deltax = fabs(1 / rc.raydirx);
		if (rc.raydiry == 0)
			rc.deltay = 1e30;
		else
			rc.deltay = fabs(1 / rc.raydiry);
		if (rc.raydirx < 0)
		{
			rc.start = -1;
			rc.sidex = (info->posx - rc.mapx) * rc.deltax;
		}
		else
		{
			rc.stepx = 1;
			rc.sidex = (rc.mapx + 1.0 - info->posx) * rc.deltax;
		}
		if (rc.raydiry < 0)
		{
			rc.stepy = -1;
			rc.sidey = (info->posy - rc.mapy) * rc.deltay;
		}
		else
		{
			rc.stepy = 1;
			rc.sidey = (rc.mapy + 1.0 - info->posy) * rc.deltay;
		}
		check_hit(info, &rc);
		line_height(&rc);
	}
	return (0);
}
