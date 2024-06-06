/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:12:10 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/06 18:12:12 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	flags_di(t_format *form, int arg)
{
	int	sign;

	sign = 0;
	if (form->flags[FLAG_plus] || arg < 0)
	{
		if (arg < 0)
			form->flags[FLAG_plus] = '-';
		else
			form->flags[FLAG_plus] = '+';
		form->flags[FLAG_space] = 0;
		sign = 1;
	}
	if (form->flags[FLAG_space])
		sign = 1;
	return (sign);
}

static int	write_data(int arg, int len)
{
	int		divide;
	int		tmp;
	int		sign;
	char	c;

	if (len == 0)
		return (1);
	divide = 1;
	tmp = len;
	sign = 1;
	if (arg < 0)
		sign = -1;
	while (tmp-- > 1)
		divide = divide * 10;
	while (divide > 0)
	{
		c = (arg / divide * sign) + '0';
		if (write(1, &c, 1) < 0)
			return (-1);
		arg = arg % divide;
		divide = divide / 10;
	}
	return (1);
}

static int	write_out(t_format *form, int arg, int w, int p)
{
	char	c;
	char	sign;

	c = ' ';
	if (form->flags[FLAG_zero])
		c = '0';
	sign = form->flags[FLAG_plus];
	if (form->flags[FLAG_space])
		sign = ' ';
	if ((form->flags[FLAG_dash])
		&& ((sign && write_char_count(sign, 1) < 0)
			|| (write_char_count('0', p)) < 0
			|| (write_data(arg, form->len)) < 0
			|| (write_char_count(c, w) < 0)))
		return (-1);
	if (!(form->flags[FLAG_dash])
		&& ((sign && form->flags[FLAG_zero] && write_char_count(sign, 1) < 0)
			|| (write_char_count(c, w) < 0)
			|| (sign && !form->flags[FLAG_zero]
				&& write_char_count(sign, 1) < 0)
			|| write_char_count('0', p) < 0
			|| write_data(arg, form->len) < 0))
		return (-1);
	return (1);
}

static int	write_printf_di(t_format *form, int arg, int sign)
{
	int	w;
	int	p;

	w = 0;
	p = 0;
	if (form->precision >= 0)
	{
		if (form->len < form->precision)
			p = form->precision - form->len;
		if (form->size > form->len + p + sign)
			w = form->size - form->len - p - sign;
	}
	else if (form->size > form->len + sign)
		w = form->size - form->len - sign;
	if (write_out(form, arg, w, p) < 0)
		return (-1);
	return (1);
}

int	ft_printf_di(int arg, t_format *form, t_static *data)
{
	int	sign;

	if (arg == 0 && form->precision == 0)
		form->len = 0;
	else
		form->len = count_digit_int(arg);
	sign = flags_di(form, arg);
	form->size = form->len + sign;
	if (form->precision > form->len)
		form->size = form->precision + sign;
	if (form->size < form->width)
		form->size = form->width;
	if (form->size < 0 || form->size >= INT_MAX - data->size - data->cur_res)
		return (-1);
	if (data->size > 0 && write(1, data->start, data->size) < 0)
		return (-1);
	if (write_printf_di(form, arg, sign) < 0)
		return (-1);
	return (form->size + data->size + data->cur_res);
}
