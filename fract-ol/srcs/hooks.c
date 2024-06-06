/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:46:19 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/26 20:46:31 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_hook(t_params *params)
{
	mlx_hook(params->display.win, DestroyNotify,
		Button1MotionMask, exit_hook, params);
	mlx_hook(params->display.win, ButtonPress, ButtonPressMask,
		zoom_hook, params);
	mlx_hook(params->display.win, KeyRelease, KeyReleaseMask, key_hook, params);
}

int	zoom_hook(int button, int x, int y, t_params *params)
{
	if (button == ZOOM_IN)
	{
		params->f.cx = params->f.lx + params->f.ix * x;
		params->f.cy = params->f.ry - params->f.iy * y;
		params->f.ix = params->f.ix / 1.4;
		params->f.iy = params->f.iy / 1.4;
		params->f.lx = params->f.cx - params->f.ix * x;
		params->f.ry = params->f.cy + params->f.iy * y;
		render_set(params);
	}
	else if (button == ZOOM_OUT)
	{
		params->f.cx = params->f.lx + params->f.ix * x;
		params->f.cy = params->f.ry - params->f.iy * y;
		params->f.ix = params->f.ix / 0.6;
		params->f.iy = params->f.iy / 0.6;
		params->f.lx = params->f.cx - params->f.ix * x;
		params->f.ry = params->f.cy + params->f.iy * y;
		render_set(params);
	}
	return (1);
}

int	key_hook(int key, t_params *params)
{
	if (key == ESCAPE)
		free_mlx(&(params->display));
	else if (key == LEFT_ARROW)
	{
		params->f.lx -= SIZE / 10 * 2 * params->f.ix;
		render_set(params);
	}
	else if (key == RIGHT_ARROW)
	{
		params->f.lx += SIZE / 10 * 2 * params->f.ix;
		render_set(params);
	}
	else if (key == UP_ARROW)
	{
		params->f.ry += SIZE / 10 * 2 * params->f.iy;
		render_set(params);
	}
	else if (key == DOWN_ARROW)
	{
		params->f.ry -= SIZE / 10 * 2 * params->f.iy;
		render_set(params);
	}
	else if (key == SHIFT_COLOR)
		change_color(params);
	return (1);
}

int	exit_hook(t_params *params)
{
	free_mlx(&(params->display));
	return (1);
}
