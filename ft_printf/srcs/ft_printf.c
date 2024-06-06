/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:22:56 by pphuangt          #+#    #+#             */
/*   Updated: 2023/12/19 16:22:58 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	write_char_count(char c, int count)
{
	char	*buff[10];

	if (count >= 10)
		ft_memset(buff, c, 10);
	while (count >= 10)
	{
		if (write(1, buff, 10) < 0)
			return (-1);
		count -= 10;
	}
	while (count-- > 0)
	{
		if (write(1, &c, 1) < 0)
			return (-1);
	}
	return (1);
}

static int	ft_parse(va_list *arg, t_format *form, t_static	*data, int *res)
{
	if (form->flags[FLAG_dash] || form->precision >= 0)
		form->flags[FLAG_zero] = 0;
	if (form->conversion == 'u')
		*res = ft_printf_unsigned(va_arg(*arg, unsigned int), form, data);
	else if (form->conversion == 'd' || form->conversion == 'i')
		*res = ft_printf_di(va_arg(*arg, int), form, data);
	else if (form->conversion == 's')
		*res = ft_printf_s(va_arg(*arg, char *), form, data);
	else if (form->conversion == 'x' || form->conversion == 'X')
		*res = ft_printf_hex(va_arg(*arg, unsigned int), form, data);
	else if (form->conversion == 'p')
		*res = ft_printf_p(va_arg(*arg, size_t), form, data);
	else if (form->conversion == 'c')
		*res = ft_printf_c(va_arg(*arg, int), form, data);
	else if (form->conversion == '%')
		*res = ft_printf_c('%', form, data);
	else
		*res = ft_printf_c(form->conversion, form, data);
	return (*res);
}

static int	pc(const char *format, va_list *arg, t_format *form, t_static *data)
{
	int	res;
	int	i;
	int	size;

	res = 0;
	i = -1;
	size = 0;
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
		{
			init_t_static(data, format + i - size, size, res);
			init_t_format(form);
			i = i + set_flags(form, format + i + 1, arg);
			if (ft_parse(arg, form, data, &res) < 0)
				return (-1);
			size = 0;
		}
		else
			size++;
	}
	if ((res >= INT_MAX - size)
		|| (size > 0 && write(1, format + i - size, size) < 0))
		return (-1);
	return (res + size);
}

int	ft_printf(const char *format, ...)
{
	va_list		arg;
	int			res;
	t_format	form;
	t_static	data;

	va_start(arg, format);
	res = pc(format, &arg, &form, &data);
	va_end(arg);
	return (res);
}
