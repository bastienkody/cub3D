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

t_img	*create_xpm_image(void *mlx_ptr, char *path)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->ptr = mlx_xpm_file_to_image(mlx_ptr, path, &(img->width), &(img->height));
	if (!img->ptr)
		return (print_error(BAD_XPM_FILE, path), NULL);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len, \
	&img->endian);
	if (!img->addr)
		return (print_error("pb with mlx get data addr for:", path), NULL);
	return (img);
}
