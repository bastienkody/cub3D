/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kody <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:49:35 by kody              #+#    #+#             */
/*   Updated: 2024/02/05 17:49:38 by kody             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/*	draw a vertical colored line on img from (x, y[0]) to (x, y[1])	*/
void	draw_vert_line(t_img *img, int x, int y[2], int color)
{
	while (++y[0] - 1 < y[1])
		pixel_w(img, x, y[0] - 1, color);
}

t_bresenham	bresenham_prep(int a[2], int b[2])
{
	t_bresenham	data;

	data.dx = abs(b[0] - a[0]);
	data.dy = abs(b[1] - a[1]);
	if (a[0] < b[0])
		data.sx = 1;
	else
		data.sx = -1;
	if (a[1] < b[1])
		data.sy = 1;
	else
		data.sy = -1;
	if (data.dx > data.dy)
		data.err = data.dx / 2;
	else
		data.err = -data.dy / 2;
	return (data);
}

/*	bresenham algo w/ a[0]=x, a[1]=y	*/
void	draw_line(t_img *img, int a[2], int b[2], int color)
{
	t_bresenham	data;
	int			err2;

	data = bresenham_prep(a, b);
	while (a[0] != b[0] || a[1] != b[1])
	{
		pixel_w(img, a[0], a[1], color);
		err2 = data.err;
		if (err2 > -data.dx)
		{
			data.err -= data.dy; 
			a[0] += data.sx; 
		}
		if (err2 < data.dy)
		{
			data.err += data.dx; 
			a[1] += data.sy; 
		}
	}
	if (a[0] >= 0 && a[0] < MNAP_S && a[1] >= 0 && a[1] < MNAP_S)
		pixel_w(img, a[0], a[1], color);
}

/*	mod for the minimap rays not to overlap (or lack) on wall by 1 pixel	*/
void	draw_line_ray(t_img *img, int a[2], int b[2], int color)
{
	t_bresenham	data;
	int			err2;

	data = bresenham_prep(a, b);
	while (a[0] != b[0] || a[1] != b[1])
	{
		if (a[0] >= 0 && a[0] <= MNAP_S && a[1] >= 0 && a[1] <= MNAP_S)
			if (get_color(img, a[0], a[1]) != GREY)
				pixel_w(img, a[0], a[1], color);
		err2 = data.err;
		if (err2 > -data.dx)
		{
			data.err -= data.dy; 
			a[0] += data.sx; 
		}
		if (err2 < data.dy)
		{
			data.err += data.dx; 
			a[1] += data.sy; 
		}
	}
	if (a[0] >= 0 && a[0] <= MNAP_S && a[1] >= 0 && a[1] <= MNAP_S)
		if (get_color(img, a[0], a[1]) != GREY)
			pixel_w(img, a[0], a[1], color);
}
