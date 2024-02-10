#include "../../inc/cub3D.h"

//Color Black will not be drawn, used as transparent color (0, 0, 0);
void	pixel_w_alpha(t_img *img, int x, int y, int color)
{
    char	*dst;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    if ((unsigned int)color == 0xFF000000)
		return ;
	*(t_uint *)dst = color;
}