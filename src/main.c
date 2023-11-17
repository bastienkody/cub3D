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
	print_info(info);
	init_display(info);
	return (end_free(info), 0);
}
