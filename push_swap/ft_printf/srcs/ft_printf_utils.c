/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:31:53 by pphuangt          #+#    #+#             */
/*   Updated: 2023/12/29 15:31:54 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	init_t_format(t_format *form)
{
	size_t	i;

	i = 0;
	form->len = 0;
	while (i < TFLAGS)
		form->flags[i++] = '\0';
	form->width = 0;
	form->precision = -1;
	form->conversion = '\0';
	form->size = 0;
}

void	init_t_static(t_static *data, const char *start, int size, int res)
{
	data->start = start;
	data->size = size;
	data->cur_res = res;
}

int	count_digit_unsigned(unsigned int arg, t_num base)
{
	int	res;
	int	base_num;

	if (arg == 0)
		return (1);
	res = 0;
	base_num = 10;
	if (base == HEX)
		base_num = 16;
	while (arg > 0)
	{
		res++;
		arg = arg / base_num;
	}
	return (res);
}

int	count_digit_int(int arg)
{
	int	res;

	res = 0;
	if (arg == 0)
		return (1);
	while (arg != 0)
	{
		res++;
		arg = arg / 10;
	}
	return (res);
}

int	count_digit_sizet(size_t arg)
{
	int	res;

	res = 0;
	if (arg == 0)
		return (1);
	while (arg > 0)
	{
		res++;
		arg = arg / 16;
	}
	return (res);
}
