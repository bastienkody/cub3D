#include <stdio.h>
#include <math.h>

void	get_sinus(void)
{
	int		angle = -1;
	double		ang_rad = M_PI / 180;

	while (++angle < 361)
		printf("# define SIN%i %f\n", angle, sin(angle * ang_rad));
}

void	get_tangeante(void)
{
	int		angle = -1;
	double		ang_rad = M_PI / 180;

	while (++angle < 361)
		printf("# define TAN%i %f\n", angle, tan(angle * ang_rad));
}

int	main(void)
{
	get_tangeante();
}
