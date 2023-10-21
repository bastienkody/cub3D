/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:41:58 by bguillau          #+#    #+#             */
/*   Updated: 2023/10/16 15:42:38 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	print_data(t_data *data)
{
	int	i;

	if (!data)
		return ((void)ft_fprintf(1, "Data addr is NULL\n"));
	ft_fprintf(1, "nopath:%i\n", data->no_path);
	ft_fprintf(1, "sopath:%i\n", data->so_path);
	ft_fprintf(1, "wepath:%i\n", data->we_path);
	ft_fprintf(1, "eapath:%i\n", data->ea_path);
	i = -1;
	ft_fprintf(1, "Floor color : ");
	while (++i < 3)
		ft_fprintf(1, "%i,", data->floor_rgb[i]);
	i = -1;
	ft_fprintf(1, "\nCeiling color : ");
	while (++i < 3)
		ft_fprintf(1, "%i,", data->ceil_rgb[i]);
	while (data->map && *(data->map))
	{
		ft_fprintf(1, "%s\n", *(data->map));
		data->map++;
	}
}
