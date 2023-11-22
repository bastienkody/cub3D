/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:53:19 by bguillau          #+#    #+#             */
/*   Updated: 2023/11/17 16:39:33 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	load_textures(t_info *info)
{
	info->intro1 = create_xpm_image(info->ptr, \
		"map/textures/intrologo/logo_pink_white_0.xpm", WIN_W, WIN_H);
	info->intro2 = create_xpm_image(info->ptr, \
		"map/textures/intrologo/logo_pink_white_1.xpm", WIN_W, WIN_H);
	ft_fprintf(1, "path:%s\n", info->no_path);
	ft_fprintf(1, "path:%s\n", info->so_path);
	ft_fprintf(1, "path:%s\n", info->we_path);
	ft_fprintf(1, "path:%s\n", info->ea_path);
	info->n_text = create_xpm_image(info->ptr, info->no_path, TILE_S, TILE_S);
	info->s_text = create_xpm_image(info->ptr, info->so_path, TILE_S, TILE_S);
	info->w_text = create_xpm_image(info->ptr, info->we_path, TILE_S, TILE_S);
	info->e_text = create_xpm_image(info->ptr, info->ea_path, TILE_S, TILE_S);
	if (!info->intro1 || !info->intro1->ptr || !info->intro2 || \
		!info->intro2->ptr || !info->n_text || !info->n_text->ptr || \
		!info->s_text || !info->s_text->ptr ||!info->w_text || \
		!info->w_text->ptr || !info->e_text || !info->e_text->ptr)
		return (print_error(XPM_LOAD, NULL), 0);
	return (1);
}

int	init_display(t_info *info)
{
	info->ptr = mlx_init();
	if (!info->ptr)
		return (print_error(BAD_INI, NULL), 0);
	info->win = mlx_new_window(info->ptr, WIN_W, WIN_H, "Cub3D");
	if (!info->win)
		return (print_error(BAD_WIN, NULL), 0);
	info->is_intro = true;
	if (!load_textures(info))
		return (0);
	return (1);
}

void	game(t_info *info)
{
	if (!init_display(info))
		return ;
	mlx_key_hook(info->win, &key_inputs, info);
	mlx_hook(info->win, 17, 0, &close_window, info);
	mlx_loop_hook(info->ptr, &disp_intro, info);
	mlx_loop(info->ptr);
}
