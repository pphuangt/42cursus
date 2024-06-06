/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:15:50 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/23 12:16:14 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	change_color(t_params *params)
{
	params->color_shift += 10;
	if (params->color_shift < 0)
		params->color_shift = 0;
	render_set(params);
}

int	get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	init_palette(int *palette)
{
	int		i;

	i = 0;
	palette[i++] = get_rgb(66, 30, 15);
	palette[i++] = get_rgb(25, 7, 26);
	palette[i++] = get_rgb(9, 1, 47);
	palette[i++] = get_rgb(4, 4, 73);
	palette[i++] = get_rgb(0, 7, 100);
	palette[i++] = get_rgb(12, 44, 138);
	palette[i++] = get_rgb(24, 82, 177);
	palette[i++] = get_rgb(57, 125, 209);
	palette[i++] = get_rgb(134, 181, 229);
	palette[i++] = get_rgb(211, 236, 248);
	palette[i++] = get_rgb(241, 233, 191);
	palette[i++] = get_rgb(248, 201, 95);
	palette[i++] = get_rgb(255, 170, 0);
	palette[i++] = get_rgb(204, 128, 0);
	palette[i++] = get_rgb(153, 87, 0);
	palette[i++] = get_rgb(106, 52, 3);
}
