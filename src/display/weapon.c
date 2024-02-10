/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:52:19 by maburnet          #+#    #+#             */
/*   Updated: 2024/02/10 11:56:26 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int create_pistol(t_info *info)
{
	ft_bzero(&info->pistol, sizeof(t_weapon));
	info->pistol.frame = 0;
	info->pistol.ammo = 100;
	info->pistol.img[0] = create_xpm_image(info->ptr, "map/textures/pistol.xpm");
	info->pistol.img[1] = create_xpm_image(info->ptr, "map/textures/pistol_fire.xpm");
	info->pistol.img[2] = create_xpm_image(info->ptr, "map/textures/pistol_recoil1.xpm");
	info->pistol.img[3] = create_xpm_image(info->ptr, "map/textures/pistol_recoil2.xpm");
	if (!info->pistol.img[0] || !info->pistol.img[1] || !info->pistol.img[2] || !info->pistol.img[3])
	{
		fprintf(stderr, "Failed to initialize pistol.xpm\n");
		return (end_free(info), -1);
	}
	info->pistol.sizex = info->pistol.img[0]->width;
	info->pistol.sizey = info->pistol.img[0]->height;
	info->pistol.posx = WIN_W / 2 - info->pistol.sizex / 2;
	info->pistol.posy = WIN_H - info->pistol.sizey + 1;
	fprintf(stderr, "ammo %d, size x%d y%d, pos x%d y %d\n", info->pistol.ammo, info->pistol.sizex, info->pistol.sizey, info->pistol.posx, info->pistol.posy);
	fprintf(stderr, "GUN CREATED\n");
	return (0);
}

int draw_pistol(t_info *info)
{
	t_weapon pistol;

	pistol = info->pistol;
	pistol.sizex = pistol.img[pistol.frame]->width;
	pistol.sizey = pistol.img[pistol.frame]->height;
	pistol.posx = WIN_W / 2 - pistol.sizex / 2;
	pistol.posy = WIN_H - pistol.sizey + 1;
	img_to_img(pistol.img[pistol.frame], info->rc, (int []){pistol.posx, pistol.posy},
		(int []){pistol.sizex, pistol.sizey});
	return (0);
}

int	fire_pistol(t_info *info)
{
	static int		counter = 0;
	int		old_frame;

	if (info->pistol.fire == 0)
		return (0);
	old_frame = info->pistol.frame;
	if (counter < 500)
		info->pistol.frame = 0;
	if (counter >= 500 && counter < 750)
		info->pistol.frame = 1;
	if (counter >= 750 && counter < 1000)
		info->pistol.frame = 2;
	if (counter >= 1000 && counter < 1250)
		info->pistol.frame = 3;
	if (counter >= 1250)
	{
		info->pistol.frame = 0;
		counter = 0;
		info->pistol.fire = 0;
	}
	if (info->pistol.frame != old_frame)
		raycast_launcher(info);
	counter++;
	return (0);
}

int game_mouse_inputs(int button, t_info *info)
{
	if (button != 1)
		return (0);
	info->pistol.fire = 1;
	return (0);
}