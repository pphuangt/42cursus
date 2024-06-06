/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:35:09 by pphuangt          #+#    #+#             */
/*   Updated: 2023/12/13 19:00:19 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include "../libft/libft.h"

# define FLAGS "0- +#"
# define CVSS "cspdiuxX%"
# define HEXU "0123456789ABCDEF"
# define PHEXU "0X"
# define HEXL "0123456789abcdef"
# define PHEXL "0x"
# define TFLAGS 5

typedef enum s_num
{
	DEC,
	HEX,
}	t_num;

typedef enum s_flags
{
	FLAG_zero = 0,
	FLAG_dash,
	FLAG_space,
	FLAG_plus,
	FLAG_sharp,
}	t_flags;

typedef struct s_static
{
	const char	*start;
	int			size;
	int			cur_res;
}	t_static;

typedef struct s_format
{
	int		len;
	char	flags[TFLAGS];
	int		width;
	int		precision;
	char	conversion;
	int		size;
}	t_format;

/* core */
int		ft_printf(const char *format, ...)
		__attribute__((format(printf, 1, 2)));
int		set_flags(t_format *form, const char *flags, va_list *arg);
/* conversion */
int		ft_printf_c(int arg, t_format *form, t_static *data);
int		ft_printf_unsigned(unsigned int arg, t_format *form, t_static *data);
int		ft_printf_di(int arg, t_format *form, t_static *data);
int		ft_printf_s(char *arg, t_format *form, t_static *data);
int		ft_printf_hex(unsigned int arg, t_format *form, t_static *data);
int		ft_printf_p(size_t arg, t_format *form, t_static *data);
/* utils */
void	init_t_format(t_format *form);
void	init_t_static(t_static *data, const char *start, int size, int res);
int		write_char_count(char c, int count);
int		count_digit_unsigned(unsigned int arg, t_num base);
int		count_digit_int(int arg);
int		count_digit_sizet(size_t arg);

#endif
