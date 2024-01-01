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

int	load_textures(t_info *info, t_parser *pars)
{
	info->intro1 = create_xpm_image(info->ptr, \
		"map/textures/intrologo/logo_pink_green_0.xpm", WIN_W, WIN_H);
	info->intro2 = create_xpm_image(info->ptr, \
		"map/textures/intrologo/logo_pink_green_1.xpm", WIN_W, WIN_H);
	info->outro[0] = create_xpm_image(info->ptr, "map/textures/outro/outro3.xpm", \
		WIN_W, WIN_H);
	info->outro[1] = create_xpm_image(info->ptr, "map/textures/outro/outro3_r.\
xpm", WIN_W, WIN_H);
	info->outro[2] = create_xpm_image(info->ptr, "map/textures/outro/outro3_q.\
xpm", WIN_W, WIN_H);
	info->n_text = create_xpm_image(info->ptr, pars->no_path, TILE_S, TILE_S);
	info->s_text = create_xpm_image(info->ptr, pars->so_path, TILE_S, TILE_S);
	info->w_text = create_xpm_image(info->ptr, pars->we_path, TILE_S, TILE_S);
	info->e_text = create_xpm_image(info->ptr, pars->ea_path, TILE_S, TILE_S);
	info->maximap = create_image(info->ptr, WIN_W, WIN_H);
	info->fminimap = create_image(info->ptr, (int)ft_strlen(*info->map) * \
	MNAP_TS, tab_len(info->map) * MNAP_TS);
	info->minimap = create_image(info->ptr, MNAP_W, MNAP_H);
	if (!info->intro1 || !info->intro1->ptr || !info->intro2 || !info->outro[0]\
		 || !info->outro[0]->ptr || !info->outro[1] || !info->outro[1]->ptr || \
		!info->outro[2] || !info->outro[2]->ptr ||!info->intro2->ptr || \
		!info->n_text || !info->n_text->ptr || !info->s_text || \
		!info->s_text->ptr || !info->w_text || !info->w_text->ptr || \
		!info->e_text || !info->e_text->ptr || !info->minimap\
		 || !info->minimap->ptr || !info->maximap || !info->maximap->ptr )
		return (0);
	return (1);
}

int	init_display(t_info *info, t_parser *pars)
{
	info->ptr = mlx_init();
	if (!info->ptr)
		return (print_error(BAD_INI, NULL), 0);
	info->win = mlx_new_window(info->ptr, WIN_W, WIN_H, "Cub3D");
	if (!info->win)
		return (print_error(BAD_WIN, NULL), 0);
	info->is_intro = true;
	if (!load_textures(info, pars))
		return (0);
	draw_first_maximap(info);
	return (1);
}
