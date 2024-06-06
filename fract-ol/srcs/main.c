/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:40:47 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/21 14:41:10 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_image(t_display *display)
{
	int	errsv;

	errsv = 0;
	display->img.ptr = mlx_new_image(display->mlx, SIZE, SIZE);
	display->tmp.ptr = mlx_new_image(display->mlx, SIZE, SIZE);
	if (!display->img.ptr || !display->tmp.ptr)
	{
		errsv = errno;
		mlx_clear_window(display->mlx, display->win);
		mlx_destroy_window(display->mlx, display->win);
		mlx_destroy_display(display->mlx);
		error_exit("MLX: can't create new image", errsv);
	}
	display->img.addr = mlx_get_data_addr(display->img.ptr,
			&(display->img.bpp), &(display->img.sl), &(display->img.endian));
	display->img.opp = display->img.bpp / 8;
	display->tmp.addr = mlx_get_data_addr(display->tmp.ptr,
			&(display->tmp.bpp), &(display->tmp.sl), &(display->tmp.endian));
	display->tmp.opp = display->tmp.bpp / 8;
	display->img.next = &(display->tmp);
	display->tmp.next = &(display->img);
	display->cur = &(display->img);
}

static void	init_display(t_display *display)
{
	int	errsv;

	errsv = 0;
	display->mlx = mlx_init();
	if (!display->mlx)
		error_exit("MLX: can't init mlx", errno);
	display->win = mlx_new_window(display->mlx, SIZE, SIZE, "fractol");
	if (!display->win)
	{
		errsv = errno;
		mlx_destroy_display(display->mlx);
		error_exit("MLX: can't create new window", errsv);
	}
	init_image(display);
}

static int	is_invalid(t_params *params, int argc, char **argv)
{
	size_t	len;

	params->f.func = NULL;
	if (argc > 1)
		len = ft_strlen(argv[1]);
	if (argc == 2)
	{
		if ((len == 2 && !ft_strncmp("-m", argv[1], len))
			|| (len == 12 && !ft_strncmp("--mandelbrot", argv[1], len)))
			init_mandelbrot(&(params->f));
		else if ((len == 2 && !ft_strncmp("-b", argv[1], len))
			|| (len == 14 && !ft_strncmp("--burning_ship", argv[1], len)))
			init_burning_ship(&(params->f));
	}
	else if (argc == 4 && ((len == 2 && !ft_strncmp("-j", argv[1], len))
			|| (len == 7 && !ft_strncmp("--julia", argv[1], len))))
	{
		if (init_julia(&(params->f), argv[2], argv[3]) < 0)
			return (1);
	}
	params->color_shift = 0;
	if (params->f.func)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_params	params;
	int			a;

	if (is_invalid(&params, argc, argv))
	{
		usage();
		return (0);
	}
	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		params.display.local_endian = 1;
	else
		params.display.local_endian = 0;
	init_display(&(params.display));
	init_palette(params.palette);
	render_set(&params);
	controls();
	init_hook(&params);
	mlx_loop(params.display.mlx);
	mlx_destroy_display(params.display.mlx);
	free(params.display.mlx);
	return (0);
}
