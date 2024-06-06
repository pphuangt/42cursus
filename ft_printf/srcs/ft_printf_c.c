/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:11:19 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/05 18:11:20 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	write_printf_c(t_format *form, int arg)
{
	int		w;

	w = 0;
	if (form->size > form->len)
		w = form->size - form->len;
	if (form->conversion)
	{
		if (form->flags[FLAG_dash])
		{
			if (write_char_count(arg, 1) < 0)
				return (-1);
			if (write_char_count(' ', w) < 0)
				return (-1);
		}
		else
		{
			if (write_char_count(' ', w) < 0)
				return (-1);
			if (write_char_count(arg, 1) < 0)
				return (-1);
		}
	}
	return (1);
}

int	ft_printf_c(int arg, t_format *form, t_static *data)
{
	form->len = 1;
	if (!form->conversion)
		form->len = 0;
	form->size = form->len;
	if (form->size < form->width)
		form->size = form->width;
	if (form->size < 0 || form->size >= INT_MAX - data->size - data->cur_res)
		return (-1);
	if (data->size > 0 && write(1, data->start, data->size) < 0)
		return (-1);
	if (write_printf_c(form, arg) < 0)
		return (-1);
	if (!form->conversion)
		return (form->len + data->size + data->cur_res);
	return (form->size + data->size + data->cur_res);
}
