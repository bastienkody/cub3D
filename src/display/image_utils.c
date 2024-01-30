/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:38:05 by bguillau          #+#    #+#             */
/*   Updated: 2023/11/17 16:38:06 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/*	write a pixel in a given color to an img	*/
void	pixel_w(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(t_uint *)dst = color;
}

/*	fetch pixel color at specific pos from an img	*/
unsigned int	get_color(t_img *img, int x, int y)
{
	return (*(t_uint *)(img->addr + (y * img->line_len + x * (img->bpp / 8))));
}

/*	copy dim pixels starting at og, from src img into dst img
	og, dim, img sizes not checked : user responsability	*/
void	img_to_img(t_img *src, t_img *dst, int og[2], int dim[2])
{
	int				x;
	int				y;
	unsigned int	color;
	const int		end[2] = {og[0] + dim[0], og[1] + dim[1]};

	x = og[0] - 1;
	while (++x <= end[0])
	{
		y = og[1] - 1;
		while (++y <= end[1])
		{
			color = get_color(src, x, y);
			pixel_w(dst, x, y, color);
		}
	}
}

t_img	*create_image(void *mlx_ptr, int w, int h)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->ptr = mlx_new_image(mlx_ptr, w, h);
	if (!img->ptr)
		return (print_error(IMAGE_FAIL, NULL), NULL);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len, \
	&img->endian);
	return (img);
}

t_img	*create_xpm_image(void *mlx_ptr, char *path, int w, int h)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->ptr = mlx_xpm_file_to_image(mlx_ptr, path, &w, &h);
	if (!img->ptr)
		return (print_error(BAD_XPM_FILE, path), NULL);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len, \
	&img->endian);
	if (!img->addr)
		return (print_error("pb with mlx get data addr for:", path), NULL);
	return (img);
}
