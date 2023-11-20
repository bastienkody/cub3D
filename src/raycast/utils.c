/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:10:14 by bguillau          #+#    #+#             */
/*   Updated: 2023/11/20 12:10:16 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

double	rad(double ang_in_degrees)
{
	const double	mod = M_PI / 180;

	return (ang_in_degrees * mod);
}

