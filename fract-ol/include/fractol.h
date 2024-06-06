/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:39:01 by pphuangt          #+#    #+#             */
/*   Updated: 2024/03/10 16:30:06 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <X11/X.h>
# include "mlx.h"
# include "ft_printf.h"
# define SIZE 800
# define MAX_ITER 42
# define PALETTE_SIZE 16

typedef struct s_params	t_params;

typedef enum s_keys
{
	ESCAPE = 0xFF1B,
	LEFT_ARROW = 0xFF51,
	RIGHT_ARROW = 0xFF53,
	UP_ARROW = 0xFF52,
	DOWN_ARROW = 0xFF54,
	ZOOM_IN = 0x04,
	ZOOM_OUT = 0x05,
	SHIFT_COLOR = 0x63
}	t_keys;

typedef struct s_func
{
	double	lx;
	double	rx;
	double	ly;
	double	ry;
	int		px;
	int		py;
	double	cx;
	double	cy;
	double	zx;
	double	zy;
	double	ix;
	double	iy;
	double	jx;
	double	jy;
	void	(*func)(t_params *params, char *dst);
}	t_func;

typedef struct s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				opp;
	int				sl;
	int				endian;
	struct s_img	*next;
}	t_img;

typedef struct s_display
{
	void	*mlx;
	void	*win;
	t_img	*cur;
	t_img	img;
	t_img	tmp;
	int		local_endian;
}	t_display;

struct s_params
{
	t_display	display;
	t_func		f;
	int			color_shift;
	int			palette[PALETTE_SIZE];
};

void	init_hook(t_params *params);
int		key_hook(int key, t_params *params);
int		zoom_hook(int button, int x, int y, t_params *params);
int		exit_hook(t_params *params);

void	render_set(t_params *params);
void	init_mandelbrot(t_func *f);
int		init_julia(t_func *f, char *cx, char *cy);
void	init_burning_ship(t_func *f);
void	mandelbrot(t_params *params, char *dst);
void	julia(t_params *params, char *dst);
void	burning_ship(t_params *params, char *dst);

int		get_rgb(int r, int g, int b);
void	init_palette(int *palette);
void	change_color(t_params *params);

int		usage(void);
void	controls(void);

void	free_mlx(t_display *display);
void	error_exit(char *str, int code);

#endif
