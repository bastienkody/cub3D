/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:37:30 by bguillau          #+#    #+#             */
/*   Updated: 2023/11/17 16:37:32 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	pixel_w(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/*	bresenham algo w/ a[0]=x, a[1]=y	*/
void	line_w(t_img *img, int a[2], int b[2], int color)
{
	const int	abs_dist[2] = {abs(b[0] - a[0]), abs(b[1] - a[1])};
	int			dir[2];
	int			err[2];
	 
	err[0] = abs_dist[0] - abs_dist[1];
	ft_memset(dir, -1, 2);
	if (a[0] < b[0])
		dir[0] = 1;
	if (a[1] < b[1])
		dir[1] = 1;
	while (a[0] != b[0] || a[1] != b[1])
	{
		pixel_w(img, a[0], a[1], color);
		err[1] = 2 * err[0];
		if (err[1] > -abs_dist[1])
		{
			err[0] -= abs_dist[1];
			a[0] += dir[0];
		}
		if (err[1] < abs_dist[0])
		{
			err[0] += abs_dist[0];
			a[1] += dir[1];
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
