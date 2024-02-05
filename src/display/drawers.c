/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   drawers.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: bguillau <bguillau@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/17 16:37:30 by bguillau		  #+#	#+#			 */
/*   Updated: 2023/11/17 16:37:32 by bguillau		 ###   ########.fr	   */
/*																			*/
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
	while (a[0]!= b[0] || a[1] != b[1])
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
}

/*	og[0] = xpos	dim[0] = w
	og[1] = ypos 	dim[1] = h	*/
void	draw_rect(t_img *img, int og[2], int dim[2], int color)
{
	int	x;
	int	y;

	x = og[0] - 1;
	while (++x <= og[0] + dim[0])
	{
		y = og[1] - 1;
		while (++y <= og[1] + dim[1])
			pixel_w(img, x, y, color);
	}
}

void	draw_border(t_img *img, int og[2], int dim[2], int color)
{
	int	x;
	int	y;

	y = og[1] - 1;
	while (++y <= og[1] + dim[1])
	{
		pixel_w(img, og[0], y, color);
		pixel_w(img, dim[0], y, color);
	}
	x = og[0] - 1;
	while (++x <= og[0] + dim[0])
	{
		pixel_w(img, x, og[1], color);
		pixel_w(img, x, dim[1], color);
	}
}

void	draw_rect_w_border(t_img *img, int og[2], int dim[2], int color)
{
	int			x;
	int			y;
	const int	end[2] = {og[0] + dim[0], og[1] + dim[1]};

	x = og[0] - 1;
	while (++x <= end[0])
	{
		y = og[1] - 1;
		while (++y <= end[1])
		{
			if (x == og[0] || x == end[0] || y == og[1] || y == end[1])
				pixel_w(img, x, y, BLACK);
			else
				pixel_w(img, x, y, color);
		}
	}
}
