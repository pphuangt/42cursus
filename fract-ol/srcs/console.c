/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:29:03 by pphuangt          #+#    #+#             */
/*   Updated: 2024/03/15 10:29:09 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	usage(void)
{
	ft_printf(">> Fract'ol Usage <<\n");
	ft_printf("\tAvailable Sets\n");
	ft_printf("1: Mandelbrot\n\t./fractol <-m or --mandelbrot>\n");
	ft_printf("2: Julia\n\t./fractol <-j or --julia> <c.r> <c.i>\n");
	ft_printf("3: Burning Ship\n\t./fractol <-b or --burning_ship>\n");
	return (0);
}

void	controls(void)
{
	ft_printf("\tControls\n");
	ft_printf(":Move around with:\n\t> Arrow keys\n");
	ft_printf(":Zoom in and out with:\n\t> Mouse wheel\n");
	ft_printf(":Change color with:\n\t> c keys\n");
	ft_printf(":To Exit press:\n\t> ESC\n");
}
