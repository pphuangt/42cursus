/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:26:14 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/08 18:26:15 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static ssize_t	is_char_flag(char flag)
{
	if (flag == '0')
		return (0);
	else if (flag == '-')
		return (1);
	else if (flag == ' ')
		return (2);
	else if (flag == '+')
		return (3);
	else if (flag == '#')
		return (4);
	return (-1);
}

static int	e_f(t_format *form, const char *flags, int *i)
{
	int		res;
	ssize_t	flag;

	res = 0;
	flag = is_char_flag(flags[*i]);
	while (flag >= 0)
	{
		form->flags[flag] = 1;
		res = 1;
		*i = *i + 1;
		flag = is_char_flag(flags[*i]);
	}
	return (res);
}

static int	e_w(t_format *form, const char *flags, int *i, va_list *arg)
{
	int	res;

	res = 0;
	if (flags[*i] == '*')
	{
		form->width = va_arg(*arg, int);
		res = 1;
		*i = *i + 1;
	}
	else if (ft_isdigit(flags[*i]))
	{
		form->width = 0;
		while (ft_isdigit(flags[*i]))
		{
			form->width = form->width * 10 + (flags[*i] - '0');
			res = 1;
			*i = *i + 1;
		}
	}
	return (res);
}

static int	e_p(t_format *form, const char *flags, int *i, va_list *arg)
{
	int	res;

	res = 0;
	if (flags[*i] == '.')
	{
		*i = *i + 1;
		form->precision = 0;
		if (flags[*i] == '*')
		{
			form->precision = va_arg(*arg, int);
			*i = *i + 1;
		}
		else
		{
			while (ft_isdigit(flags[*i]))
			{
				form->precision = form->precision * 10 + (flags[*i] - '0');
				*i = *i + 1;
			}
		}
		res = 1;
	}
	return (res);
}

int	set_flags(t_format *form, const char *flags, va_list *arg)
{
	int		is_in;
	int		i;

	is_in = 1;
	i = 0;
	while (is_in)
	{
		is_in = 0;
		is_in += e_f(form, flags, &i);
		is_in += e_w(form, flags, &i, arg);
		is_in += e_p(form, flags, &i, arg);
	}
	if (form->width < 0)
	{
		form->flags[FLAG_dash] = 1;
		if (form->width == INT_MIN)
			form->width = INT_MAX;
		else
			form->width = form->width * (-1);
	}
	form->conversion = flags[i++];
	if (!form->conversion)
		return (i - 1);
	return (i);
}
