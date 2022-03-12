/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 02:00:31 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/13 03:40:07 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->llen + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	drawframe(t_fdfvars *fdfvars)
{
	t_data	img;
	void	*mlx;
	void	*mlx_win;

	mlx = fdfvars->mlx;
	mlx_win = fdfvars->mlx_win;
	img.img = mlx_new_image(fdfvars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.llen, &img.endian);
	fdfvars->img = &img;
	rotatemap(fdfvars->arr_map, fdfvars->parsemap, fdfvars->rotateangle);
	fdfvars->arr_map = interpolatemap(fdfvars->parsemap, fdfvars);
	drawmap(fdfvars, fdfvars->img);
	mlx_put_image_to_window(mlx, mlx_win, fdfvars->img->img, 0, 0);
	return (1);
}
