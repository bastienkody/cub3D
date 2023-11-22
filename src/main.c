/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:23:33 by bguillau          #+#    #+#             */
/*   Updated: 2023/10/13 16:25:19 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	unload_texture(void *mlx_ptr, t_img *img)
{
	if (img && img->ptr)
	{
		mlx_destroy_image(mlx_ptr, img->ptr);
		free(img);
	}
}

void	end_free(t_info *info)
{
	if (info->map)
		free_charray(info->map);
	free(info->no_path);
	free(info->so_path);
	free(info->we_path);
	free(info->ea_path);
	if (info->ptr)
	{
		unload_texture(info->ptr, info->intro1);
		unload_texture(info->ptr, info->intro2);
		unload_texture(info->ptr, info->bg_default);
		unload_texture(info->ptr, info->n_text);
		unload_texture(info->ptr, info->s_text);
		unload_texture(info->ptr, info->w_text);
		unload_texture(info->ptr, info->e_text);
		if (info->win)
			mlx_destroy_window(info->ptr, info->win);
		mlx_destroy_display(info->ptr);
		free(info->ptr);
	}
	free(info);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, __attribute__((unused)) char **envp)
{
	t_info	*info;

	info = main_parser(argc, argv);
	if (!info)
		return (1);
	if (!map_checker(info))
		return (end_free(info), 1);
	game(info);
	return (end_free(info), 0);
}
