/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:34:54 by pphuangt          #+#    #+#             */
/*   Updated: 2024/03/04 09:35:01 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	free_mlx(t_display *display)
{
	mlx_destroy_image(display->mlx, display->img.ptr);
	mlx_destroy_image(display->mlx, display->tmp.ptr);
	mlx_clear_window(display->mlx, display->win);
	mlx_destroy_window(display->mlx, display->win);
	mlx_loop_end(display->mlx);
}

void	error_exit(char *str, int code)
{
	ft_putendl_fd(str, 2);
	if (code > 0)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(strerror(code), 2);
	}
	exit(1);
}
