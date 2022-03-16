/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:57:46 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/16 14:40:26 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	inithooks(void *mlx_win, t_fdfvars *fdfvars)
{
	mlx_hook(mlx_win, 2, 1L << 0, keymod, fdfvars);
	mlx_hook(mlx_win, 4, 1L << 2, mousectl, fdfvars);
	mlx_hook(mlx_win, 17, 1L << 17, end_win, fdfvars);
	mlx_hook(mlx_win, 6, 1L << 6, mouserot, fdfvars);
	mlx_hook(mlx_win, 5, 1L << 3, mouserel, fdfvars);
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
	init_arr(fdfvars);
	fdfvars->w_width = WIDTH;
	fdfvars->w_height = HEIGHT;
	fdfvars->rotateangle = 45;
	rotatemap(fdfvars->arr_map, fdfvars->parsemap, fdfvars->rotateangle);
	getdrawdim(fdfvars, fdfvars->arr_map);
	fdfvars->zoomfactor = WIDTH / (fdfvars->m_width);
	if (HEIGHT / (fdfvars->m_height) < fdfvars->zoomfactor)
		fdfvars->zoomfactor = HEIGHT / (fdfvars->m_height);
	fdfvars->def_zoom = fdfvars->zoomfactor;
	fdfvars->z_angle = 30;
	fdfvars->customcolor = 0;
	fdfvars->ele_factor = 1;
	fdfvars->mouse_pressed = 0;
	fdfvars->rmouse_pressed = 0;
}

void	init_arr(t_fdfvars *fdfvars)
{
	t_map		*map;
	t_vertex	***int_map;
	int			i;
	int			j;

	i = 0;
	map = fdfvars->parsemap;
	int_map = (t_vertex ***)malloc(map->width * sizeof(t_vertex **));
	while (i < map->width)
	{
		j = 0;
		int_map[i] = (t_vertex **)malloc(map->height * sizeof(t_vertex *));
		while (j < map->height)
		{
			int_map[i][j++] = (t_vertex *)malloc(sizeof(t_vertex));
		}
		i++;
	}
	fdfvars->arr_map = int_map;
}

void	initpadding(t_fdfvars *fdfvars)
{
	getdrawdim(fdfvars, fdfvars->arr_map);
	fdfvars->shift_x += (WIDTH - fdfvars->m_width) / 2;
	fdfvars->shift_y += (HEIGHT - fdfvars->m_height) / 2;
	fdfvars->def_shf_x = fdfvars->shift_x;
	fdfvars->def_shf_y = fdfvars->shift_y;
}
