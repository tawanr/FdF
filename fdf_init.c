/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:57:46 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/13 02:31:50 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	inithooks(void *mlx_win, t_fdfvars *fdfvars)
{
	mlx_hook(mlx_win, 3, 0, keymod, fdfvars);
	mlx_hook(mlx_win, 4, 0, mousectl, fdfvars);
	mlx_hook(mlx_win, 17, 0, end_win, fdfvars);
	mlx_hook(mlx_win, 6, 0, mouserot, fdfvars);
	mlx_hook(mlx_win, 5, 0, mouserel, fdfvars);
	mlx_loop_hook(fdfvars->mlx, drawframe, fdfvars);
}

void	init_mlx(t_fdfvars *fdfvars, void *mlx, void *mlx_win, t_data *img)
{
	fdfvars->mlx = mlx;
	fdfvars->mlx_win = mlx_win;
	fdfvars->img = img;
	return ;
}

void	init_vars(t_fdfvars *fdfvars)
{
	int			map_w;
	int			map_h;
	int			i;
	t_vertex	***int_map;
	t_map		*map;

	i = 0;
	map = fdfvars->parsemap;
	int_map = (t_vertex ***)malloc(map->width * sizeof(t_vertex **));
	while (i < map->width)
		int_map[i++] = (t_vertex **)malloc(map->height * sizeof(t_vertex *));
	fdfvars->arr_map = int_map;
	map_w = fdfvars->parsemap->width;
	map_h = fdfvars->parsemap->height;
	fdfvars->w_width = WIDTH;
	fdfvars->w_height = HEIGHT;
	fdfvars->rotateangle = 45;
	rotatemap(int_map, fdfvars->parsemap, fdfvars->rotateangle);
	getdrawdim(fdfvars, int_map);
	fdfvars->zoomfactor = WIDTH / (fdfvars->m_width);
	if (HEIGHT / (fdfvars->m_height) < fdfvars->zoomfactor)
		fdfvars->zoomfactor = HEIGHT / (fdfvars->m_height);
	fdfvars->z_angle = 30;
	fdfvars->customcolor = 0;
	fdfvars->ele_factor = 1;
}

void	initpadding(t_fdfvars *fdfvars)
{
	getdrawdim(fdfvars, fdfvars->arr_map);
	fdfvars->shift_x += (WIDTH - fdfvars->m_width) / 2;
	fdfvars->shift_y += (HEIGHT - fdfvars->m_height) / 2;
}
