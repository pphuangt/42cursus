/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:54:58 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/14 13:55:13 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_overflow(int num, int sign, char c)
{
	if (num > (INT_MAX - (c - '0')) / 10 && sign == 1)
		return (1);
	else if (num < (INT_MIN + (c - '0')) / 10 && sign == -1)
		return (1);
	return (0);
}

int	is_format(char c)
{
	if (c != ' ' && c != '+' && c != '-'
		&& !ft_isdigit(c))
		return (-1);
	return (1);
}

int	is_sign(char *arg, int *i, int *sign)
{
	*sign = 1;
	if (arg[*i] == '-' || arg[*i] == '+')
	{
		if (!ft_isdigit(arg[*i + 1]))
			return (-1);
		if (*i > 0 && ft_isdigit(arg[*i - 1]))
			return (-1);
		if (arg[*i] == '-')
			*sign = -1;
		*i = *i + 1;
	}
	return (1);
}
