
#include "../../inc/cub3D.h"

/*	most significative bit at left = big endian (1)	*/
int	get_endian(void)
{
	const int	nb = 1;

	if (*(char *)&nb == 1)
		return (1);
	else
		return (0);
}