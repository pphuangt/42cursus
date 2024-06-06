/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:40:20 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/07 20:40:24 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	write_data(unsigned int arg, int len, char conversion)
{
	unsigned int	divide;
	int				tmp;
	char			c;
	char			*base;

	if (len == 0)
		return (1);
	divide = 1;
	base = HEXL;
	if (conversion == 'X')
		base = HEXU;
	while (len-- > 1)
		divide = divide * 16;
	while (divide > 0)
	{
		tmp = arg / divide;
		c = base[tmp];
		if (write(1, &c, 1) < 0)
			return (-1);
		arg = arg % divide;
		divide = divide / 16;
	}
	return (1);
}

static int	write_out(t_format *form, unsigned int arg, int w, int p)
{
	int		sharp;
	char	c;
	char	*base;

	sharp = 0;
	if (form->flags[FLAG_sharp] && arg > 0)
		sharp = 2;
	c = ' ';
	if (form->flags[FLAG_zero])
		c = '0';
	base = PHEXL;
	if (form->conversion == 'X')
		base = PHEXU;
	if ((form->flags[FLAG_dash]) && ((sharp && arg > 0 && write(1, base, 2) < 0)
			|| write_char_count('0', p) < 0
			|| write_data(arg, form->len, form->conversion) < 0
			|| write_char_count(c, w) < 0))
		return (-1);
	if (!(form->flags[FLAG_dash]) && ((sharp && arg > 0 && c == '0'
				&& write(1, base, 2) < 0) || (write_char_count(c, w) < 0)
			|| ((sharp && arg > 0 && c == ' ') && (write(1, base, 2) < 0))
			|| (write_char_count('0', p) < 0)
			|| (write_data(arg, form->len, form->conversion) < 0)))
		return (-1);
	return (1);
}

static int	write_printf_hex(t_format *form, unsigned int arg, int sharp)
{
	int	w;
	int	p;

	w = 0;
	p = 0;
	if (form->precision >= 0)
	{
		if (form->len < form->precision)
			p = form->precision - form->len;
		if (form->size > form->len + p + sharp)
			w = form->size - form->len - p - sharp;
	}
	else if (arg != 0 && form->size > form->len + sharp)
		w = form->size - form->len - sharp;
	else if (arg == 0 && form->size > form->len + sharp)
		w = form->size - form->len;
	if (write_out(form, arg, w, p) < 0)
		return (-1);
	return (1);
}

int	ft_printf_hex(unsigned int arg, t_format *form, t_static *data)
{
	int	sharp;

	if (arg == 0 && form->precision == 0)
		form->len = 0;
	else
		form->len = count_digit_unsigned(arg, HEX);
	sharp = 0;
	if (form->flags[FLAG_sharp] && arg > 0)
		sharp = 2;
	form->size = form->len + sharp;
	if (form->precision > form->len)
		form->size = form->precision + sharp;
	if (form->size < form->width)
		form->size = form->width;
	if (form->size < 0 || form->size >= INT_MAX - data->size - data->cur_res)
		return (-1);
	if (data->size > 0 && write(1, data->start, data->size) < 0)
		return (-1);
	if (write_printf_hex(form, arg, sharp) < 0)
		return (-1);
	return (form->size + data->size + data->cur_res);
}
