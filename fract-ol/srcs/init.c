/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:35:12 by pphuangt          #+#    #+#             */
/*   Updated: 2024/03/15 10:35:18 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_mandelbrot(t_func *f)
{
	f->lx = -2.0;
	f->rx = 1.0;
	f->ly = -1.5;
	f->ry = 1.5;
	f->ix = (f->rx - f->lx) / (SIZE - 1);
	f->iy = (f->ry - f->ly) / (SIZE - 1);
	f->func = &mandelbrot;
}

int	init_julia(t_func *f, char *cx, char *cy)
{
	char	*end_cx;
	char	*end_cy;

	f->jx = ft_strtod(cx, &end_cx);
	f->jy = ft_strtod(cy, &end_cy);
	f->lx = -2.0;
	f->rx = 2.0;
	f->ly = -2.0;
	f->ry = 2.0;
	f->ix = (f->rx - f->lx) / (SIZE - 1);
	f->iy = (f->ry - f->ly) / (SIZE - 1);
	if (cx == end_cx || cy == end_cy)
		return (-1);
	f->func = &julia;
	return (1);
}

void	init_burning_ship(t_func *f)
{
	f->lx = -2.0;
	f->rx = 1.0;
	f->ly = 1.5;
	f->ry = -1.5;
	f->ix = (f->rx - f->lx) / (SIZE - 1);
	f->iy = (f->ry - f->ly) / (SIZE - 1);
	f->func = &burning_ship;
}
