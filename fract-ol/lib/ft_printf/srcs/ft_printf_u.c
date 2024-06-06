/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:08:07 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/05 23:08:08 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	write_data(unsigned int arg, int len)
{
	unsigned int	divide;
	int				tmp;
	char			c;

	if (len == 0)
		return (1);
	divide = 1;
	tmp = len;
	while (tmp-- > 1)
		divide = divide * 10;
	while (divide > 0)
	{
		c = arg / divide + '0';
		if (write(1, &c, 1) < 0)
			return (-1);
		arg = arg % divide;
		divide = divide / 10;
	}
	return (1);
}

static int	write_out(t_format *form, unsigned int arg, int w, int p)
{
	char	c;

	c = ' ';
	if (form->flags[FLAG_zero])
		c = '0';
	if (form->flags[FLAG_dash])
	{
		if (write_char_count('0', p) < 0)
			return (-1);
		if (write_data(arg, form->len) < 0)
			return (-1);
		if (write_char_count(c, w) < 0)
			return (-1);
	}
	else
	{
		if (write_char_count(c, w) < 0)
			return (-1);
		if (write_char_count('0', p) < 0)
			return (-1);
		if (write_data(arg, form->len) < 0)
			return (-1);
	}
	return (1);
}

static int	write_printf_u(t_format *form, unsigned int arg)
{
	int	w;
	int	p;

	w = 0;
	p = 0;
	if (form->precision >= 0)
	{
		if (form->len < form->precision)
			p = form->precision - form->len;
		if (form->size > form->len + p)
			w = form->size - form->len - p;
	}
	else if (form->size > form->len)
		w = form->size - form->len;
	if (write_out(form, arg, w, p) < 0)
		return (-1);
	return (1);
}

int	ft_printf_unsigned(unsigned int arg, t_format *form, t_static *data)
{
	if (arg == 0 && form->precision == 0)
		form->len = 0;
	else
		form->len = count_digit_unsigned(arg, DEC);
	form->size = form->len;
	if (form->precision > form->len)
		form->size = form->precision;
	if (form->size < form->width)
		form->size = form->width;
	if (form->size < 0 || form->size >= INT_MAX - data->size - data->cur_res)
		return (-1);
	if (data->size > 0 && write(1, data->start, data->size) < 0)
		return (-1);
	if (write_printf_u(form, arg) < 0)
		return (-1);
	return (form->size + data->size + data->cur_res);
}
