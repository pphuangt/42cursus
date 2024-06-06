/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:47:18 by pphuangt          #+#    #+#             */
/*   Updated: 2024/03/04 09:47:27 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_params *params, char *dst)
{
	double	x;
	double	y;
	int		i;

	params->f.zx = 0;
	params->f.zy = 0;
	x = 0;
	y = 0;
	i = -1;
	while ((params->f.zx + params->f.zy) <= 4 && ++i < MAX_ITER)
	{
		y = 2 * x * y + params->f.cy;
		x = params->f.zx - params->f.zy + params->f.cx;
		params->f.zx = x * x;
		params->f.zy = y * y;
	}
	if (i == MAX_ITER || i % PALETTE_SIZE == 0)
		*(unsigned int *)dst = 0;
	else
		*(unsigned int *)dst
			= params->palette[(i + params->color_shift) % PALETTE_SIZE];
}

void	julia(t_params *params, char *dst)
{
	double	tmp;
	int		i;

	params->f.zx = params->f.cx;
	params->f.zy = params->f.cy;
	i = -1;
	while ((params->f.zx * params->f.zx + params->f.zy * params->f.zy) <= 4
		&& ++i < MAX_ITER)
	{
		tmp = params->f.zx * params->f.zx - params->f.zy * params->f.zy;
		params->f.zy = 2 * params->f.zx * params->f.zy + params->f.jy;
		params->f.zx = tmp + params->f.jx;
	}
	if (i == MAX_ITER || i % PALETTE_SIZE == 0)
		*(unsigned int *)dst = 0;
	else
		*(unsigned int *)dst
			= params->palette[(i + params->color_shift) % PALETTE_SIZE];
}

void	burning_ship(t_params *params, char *dst)
{
	double	tmp;
	int		i;

	params->f.zx = 0;
	params->f.zy = 0;
	i = -1;
	while ((params->f.zx * params->f.zx + params->f.zy * params->f.zy) <= 4
		&& ++i < MAX_ITER)
	{
		tmp = params->f.zx * params->f.zx
			- params->f.zy * params->f.zy + params->f.cx;
		params->f.zy = fabs(2 * params->f.zx * params->f.zy)
			+ params->f.cy;
		params->f.zx = tmp;
	}
	if (i == MAX_ITER || i % PALETTE_SIZE == 0)
		*(unsigned int *)dst = 0;
	else
		*(unsigned int *)dst
			= params->palette[(i + params->color_shift) % PALETTE_SIZE];
}

void	render_set(t_params *params)
{
	char	*dst;

	params->f.py = -1;
	params->f.cy = params->f.ry;
	dst = params->display.cur->addr;
	while (++(params->f.py) < SIZE)
	{
		params->f.px = -1;
		params->f.cx = params->f.lx;
		while (++(params->f.px) < SIZE)
		{
			params->f.func(params, dst);
			params->f.cx += params->f.ix;
			dst += params->display.cur->opp;
		}
		params->f.cy -= params->f.iy;
	}
	mlx_put_image_to_window(params->display.mlx, params->display.win,
		params->display.cur->ptr, 0, 0);
	params->display.cur = params->display.cur->next;
}
