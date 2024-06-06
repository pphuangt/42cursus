/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:46:23 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/06 20:46:25 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	write_printf_s(t_format *form, char *arg)
{
	int	len;

	len = form->len;
	if (form->precision >= 0 && form->precision < form->len)
		len = form->precision;
	if (form->flags[FLAG_dash])
	{
		if (!arg && write(1, "(null)", len) < 0)
			return (-1);
		if (arg && write(1, arg, len) < 0)
			return (-1);
		if (write_char_count(' ', form->size - len) < 0)
			return (-1);
	}
	else
	{
		if (write_char_count(' ', form->size - len) < 0)
			return (-1);
		if (!arg && write(1, "(null)", len) < 0)
			return (-1);
		if (arg && write(1, arg, len) < 0)
			return (-1);
	}
	return (1);
}

int	ft_printf_s(char *arg, t_format *form, t_static *data)
{
	if (!arg)
		form->len = 6;
	else
		form->len = ft_strlen(arg);
	form->size = form->len;
	if (form->precision >= 0 && form->precision < form->len)
		form->size = form->precision;
	if (form->width > form->size)
		form->size = form->width;
	if (form->size < 0 || form->size >= INT_MAX - data->size - data->cur_res)
		return (-1);
	if (data->size > 0 && write(1, data->start, data->size) < 0)
		return (-1);
	if (write_printf_s(form, arg) < 0)
		return (-1);
	return (form->size + data->size + data->cur_res);
}
