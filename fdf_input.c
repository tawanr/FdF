/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:52:12 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/13 05:10:42 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	keymod(int keycode, t_fdfvars *fdfvars)
{
	if (keycode == 0x7B || keycode == 0x00)
		fdfvars->shift_x += 20;
	else if (keycode == 0x7C || keycode == 0x02)
		fdfvars->shift_x -= 20;
	else if (keycode == 0x7E || keycode == 0x0D)
		fdfvars->shift_y += 20;
	else if (keycode == 0x7D || keycode == 0x01)
		fdfvars->shift_y -= 20;
	else if (keycode == 0x0E)
		fdfvars->rotateangle += 5;
	else if (keycode == 0x0C)
		fdfvars->rotateangle -= 5;
	else if (keycode == 0x2B)
		fdfvars->zoomfactor += 2;
	else if (keycode == 0x2F)
		fdfvars->zoomfactor -= 2;
	else if (keycode == 0x1B)
		fdfvars->ele_factor -= .05;
	else if (keycode == 0x18)
		fdfvars->ele_factor += .05;
	else
		keycont(keycode, fdfvars);
	return (1);
}

void	keycont(int keycode, t_fdfvars *fdfvars)
{
	if (keycode == 0x08)
		fdfvars->customcolor = !fdfvars->customcolor;
	else if (keycode == 0x0F)
	{
		fdfvars->shift_x = (WIDTH - fdfvars->m_width) / 2;
		fdfvars->shift_y = (HEIGHT - fdfvars->m_height) / 2;
		fdfvars->rotateangle = 45;
		fdfvars->zoomfactor = WIDTH / fdfvars->m_width;
		if (HEIGHT / (fdfvars->m_height) < fdfvars->zoomfactor)
			fdfvars->zoomfactor = HEIGHT / (fdfvars->m_height);
		fdfvars->z_angle = 30;
		fdfvars->ele_factor = 1;
	}
	else if (keycode == 0x35)
		end_win(fdfvars);
}

int	mousectl(int button, int x, int y, t_fdfvars *fdfvars)
{
	if (button == 4)
		fdfvars->zoomfactor += 5;
	else if (button == 5)
		fdfvars->zoomfactor -= 5;
	else if ((button == 1 || button == 2) && (x > 0 && y > 0))
	{
		fdfvars->mouse_x = x;
		fdfvars->mouse_y = y;
		if (button == 1)
			fdfvars->mouse_pressed = 1;
		else if (button == 2)
			fdfvars->rmouse_pressed = 1;
	}
	return (1);
}

int	mouserel(int button, int x, int y, t_fdfvars *fdfvars)
{
	if (button == 1)
		fdfvars->mouse_pressed = 0;
	else if (button == 2)
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
		if (fdfvars->z_angle + (y - fdfvars->mouse_y) > 0 && \
			fdfvars->z_angle + (y - fdfvars->mouse_y) < 90)
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
