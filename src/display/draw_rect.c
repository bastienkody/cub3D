/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kody <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:48:50 by kody              #+#    #+#             */
/*   Updated: 2024/02/05 17:48:55 by kody             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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
