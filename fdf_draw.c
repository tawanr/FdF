/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 02:00:31 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/16 14:44:17 by tratanat         ###   ########.fr       */
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
	t_data	*i;
	void	*mlx;
	void	*o_img;

	mlx = fdfvars->mlx;
	o_img = fdfvars->img->img;
	i = fdfvars->img;
	i->img = mlx_new_image(fdfvars->mlx, WIDTH, HEIGHT);
	i->addr = mlx_get_data_addr(i->img, &i->bpp, &i->llen, &i->endian);
	rotatemap(fdfvars->arr_map, fdfvars->parsemap, fdfvars->rotateangle);
	fdfvars->arr_map = interpolatemap(fdfvars);
	drawmap(fdfvars, fdfvars->img);
	mlx_put_image_to_window(mlx, fdfvars->mlx_win, fdfvars->img->img, 0, 0);
	mlx_destroy_image(mlx, o_img);
	return (1);
}
