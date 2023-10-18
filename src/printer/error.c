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

void	print_error(char *str1, char *str2)
{
	ft_fprintf(2, "Error\n");
	if (str1 && *str1)
		ft_fprintf(2, "%s ", str1);
	if (!str2 && *str2)
		write(2, "\n", 1);
	else
		ft_fprintf(2, "%s\n", str2);


}
