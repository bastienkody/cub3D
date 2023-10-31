
#include "../../inc/cub3D.h"

/*	most significative bit at left for big endian (ret 1)	*/
int	get_endian(void)
{
	const int	nb = 1;

	if (*(char *)&nb == 1)
		return (0);
	else
		return (1);
}

unsigned int	argb_to_hex(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}