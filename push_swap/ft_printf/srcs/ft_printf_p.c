/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:40:32 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/07 18:40:34 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	write_data(size_t arg, int len)
{
	size_t	divide;
	size_t	tmp;
	char	c;

	if (len == 0)
		return (1);
	divide = 1;
	while (len-- > 1)
		divide = divide * 16;
	while (divide > 0)
	{
		tmp = arg / divide;
		c = HEXL[tmp];
		if (write(1, &c, 1) < 0)
			return (-1);
		arg = arg % divide;
		divide = divide / 16;
	}
	return (1);
}

static int	write_out(t_format *form, size_t arg, int w, int p)
{
	char	c;

	c = ' ';
	if (form->flags[FLAG_zero])
		c = '0';
	if (form->flags[FLAG_dash])
	{
		if (write(1, PHEXL, 2) < 0 || write_char_count('0', p) < 0
			|| write_data(arg, form->len) < 0 || write_char_count(c, w) < 0)
			return (-1);
	}
	else
	{
		if ((w > 0 && c == 48 && write(1, PHEXL, 2) < 0)
			|| write_char_count(c, w) < 0)
			return (-1);
		if ((c != 48 && write(1, PHEXL, 2) < 0) || write_char_count('0', p) < 0)
			return (-1);
		if (write_data(arg, form->len) < 0)
			return (-1);
	}
	return (1);
}

static int	write_printf_p(t_format *form, size_t arg)
{
	int	w;
	int	p;

	w = 0;
	p = 0;
	if (form->precision >= 0)
	{
		if (form->len < form->precision)
			p = form->precision - form->len;
		if (form->size > form->len + p + 2)
			w = form->size - form->len - p - 2;
	}
	else if (form->size > form->len + 2)
		w = form->size - form->len - 2;
	if (write_out(form, arg, w, p) < 0)
		return (-1);
	return (1);
}

int	ft_printf_p(size_t arg, t_format *form, t_static *data)
{
	if (arg == 0 && form->precision == 0)
		form->len = 0;
	else
		form->len = count_digit_sizet(arg);
	form->size = form->len + 2;
	if (form->precision > form->len)
		form->size = form->precision + 2;
	if (form->size < form->width)
		form->size = form->width;
	if (form->size < 0 || form->size >= INT_MAX - data->size - data->cur_res)
		return (-1);
	if (data->size > 0 && write(1, data->start, data->size) < 0)
		return (-1);
	if (write_printf_p(form, arg) < 0)
		return (-1);
	return (form->size + data->size + data->cur_res);
}
