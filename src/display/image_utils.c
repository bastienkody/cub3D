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
