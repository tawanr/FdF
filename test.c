#include <mlx.h>
#include <stdio.h>

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init() failed\n");
		return (0);
	}
	mlx_win = mlx_new_window(mlx, 800, 600, "Hello world!");
	mlx_loop(mlx);
	printf("mlx_init() successful\n");
	return (1);
}
