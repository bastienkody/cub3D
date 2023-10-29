
#include "../../inc/cub3D.h"

int	init_display(t_info *info)
{
	const int	sizex = 250;
	const int	sizey = 250;
	const char	*title = "Cub3D";

	info->ptr = mlx_init();
	if (!info->ptr)
		return (print_error(BAD_INI, NULL), 0);
	info->win = mlx_new_window(info->ptr, sizex, sizey, (char *)title);
	if (!info->win)
		return (print_error(BAD_WIN, NULL), 0);
	return (1);
}
