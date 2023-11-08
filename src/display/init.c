/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:53:19 by bguillau          #+#    #+#             */
/*   Updated: 2023/11/01 16:53:22 by bguillau         ###   ########.fr       */
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

int	init_display(t_info *info)
{
	const int	sizex = WIN_WIDTH;
	const int	sizey = WIN_HEIGHT;
	const char	*title = "Cub3D";
	t_img		*bg;
	t_img		*w1;
	t_img		*w2;

	info->ptr = mlx_init();
	if (!info->ptr)
		return (print_error(BAD_INI, NULL), 0);
	info->win = mlx_new_window(info->ptr, sizex, sizey, (char *)title);
	if (!info->win)
		return (print_error(BAD_WIN, NULL), 0);
	//info->intro1 = ft_calloc(1, sizeof(t_img *));
	//info->intro2 = ft_calloc(1, sizeof(t_img *));
	info->is_intro = true;
	bg = create_image(info->ptr, sizex, sizey);
	w1 = create_xpm_image(info->ptr, info->no_path, 64, 64);
	w2 = create_xpm_image(info->ptr, info->so_path, 0, 0);
	if (!bg || !w1 | !w2)
		return (print_error(ALLOC_FAIL, NULL), 0);
	info->intro1 = create_xpm_image(info->ptr, "map/textures/intrologo/logo_pink_white_0.xpm", 1080, 720);
	info->intro2 = create_xpm_image(info->ptr, "map/textures/intrologo/logo_pink_white_1.xpm", 1080, 720);
	if (!info->intro1 || !info->intro1->ptr || !info->intro2 || !info->intro2->ptr)
		return (print_error("intro img loading failed", NULL), 0);
	draw_rect(bg, (int[2]){0, 0}, (int[2]){64, 64}, 0xFF0015F0);
	mlx_put_image_to_window(info->ptr, info->win, bg->ptr, 65, 65);
	mlx_put_image_to_window(info->ptr, info->win, w1->ptr, 128, 0);
	mlx_put_image_to_window(info->ptr, info->win, w2->ptr, 192, 0);
	mlx_put_image_to_window(info->ptr, info->win, info->intro1->ptr, 0, 0);
	mlx_key_hook(info->win, &key_inputs, info);
	mlx_hook(info->win, 17, 0, &close_window, info);
	mlx_loop_hook(info->ptr, &disp_intro, info);
	mlx_loop(info->ptr);
	return (1);
}
