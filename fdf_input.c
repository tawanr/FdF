/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:52:12 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/16 14:42:31 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	keymod(int keycode, t_fdfvars *fdfvars)
{
	if (keycode == 100 || keycode == 65363)
		fdfvars->shift_x += 20;
	else if (keycode == 97 || keycode == 65361)
		fdfvars->shift_x -= 20;
	else if (keycode == 115 || keycode == 65364)
		fdfvars->shift_y += 20;
	else if (keycode == 119 || keycode == 65362)
		fdfvars->shift_y -= 20;
	else if (keycode == 101)
		fdfvars->rotateangle += 5;
	else if (keycode == 113)
		fdfvars->rotateangle -= 5;
	else if (keycode == 44)
		fdfvars->zoomfactor += 2;
	else if (keycode == 46)
		fdfvars->zoomfactor -= 2;
	else if (keycode == 45)
		fdfvars->ele_factor *= .9;
	else if (keycode == 61)
		fdfvars->ele_factor *= 1.1;
	else
		keycont(keycode, fdfvars);
	return (1);
}

void	keycont(int keycode, t_fdfvars *fdfvars)
{
	if (keycode == 99)
		fdfvars->customcolor = !fdfvars->customcolor;
	else if (keycode == 114)
	{
		fdfvars->shift_x = fdfvars->def_shf_x;
		fdfvars->shift_y = fdfvars->def_shf_y;
		fdfvars->rotateangle = 45;
		fdfvars->zoomfactor = fdfvars->def_zoom;
		fdfvars->z_angle = 30;
		fdfvars->ele_factor = 1;
	}
	else if (keycode == 65307)
		end_win(fdfvars);
}

int	mousectl(int button, int x, int y, t_fdfvars *fdfvars)
{
	if (button == 4)
		fdfvars->zoomfactor += 1;
	else if (button == 5)
		fdfvars->zoomfactor -= 1;
	else if ((button == 1 || button == 3) && (x > 0 && y > 0))
	{
		fdfvars->mouse_x = x;
		fdfvars->mouse_y = y;
		if (button == 1)
			fdfvars->mouse_pressed = 1;
		else if (button == 3)
			fdfvars->rmouse_pressed = 1;
	}
	return (1);
}

int	mouserel(int button, int x, int y, t_fdfvars *fdfvars)
{
	fdfvars->mouse_x = x;
	fdfvars->mouse_y = y;
	if (button == 1)
		fdfvars->mouse_pressed = 0;
	else if (button == 3)
		fdfvars->rmouse_pressed = 0;
	return (1);
}

int	mouserot(int x, int y, t_fdfvars *fdfvars)
{
	if (fdfvars->mouse_pressed == 0 && fdfvars->rmouse_pressed == 0)
		return (0);
	if (fdfvars->mouse_pressed)
	{
		fdfvars->rotateangle += (x - fdfvars->mouse_x);
		if (fdfvars->z_angle + (y - fdfvars->mouse_y) >= 0 && \
			fdfvars->z_angle + (y - fdfvars->mouse_y) <= 90)
			fdfvars->z_angle += (y - fdfvars->mouse_y);
	}
	else if (fdfvars->rmouse_pressed)
	{
		fdfvars->shift_x += (x - fdfvars->mouse_x);
		fdfvars->shift_y += (y - fdfvars->mouse_y);
	}
	fdfvars->mouse_x = x;
	fdfvars->mouse_y = y;
	return (1);
}
