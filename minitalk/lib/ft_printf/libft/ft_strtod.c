/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:54:13 by pphuangt          #+#    #+#             */
/*   Updated: 2024/03/16 13:54:23 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*do_int(const char *str, double *int_part)
{
	while (ft_isdigit((unsigned char)*str))
	{
		*int_part = *int_part * 10 + (*str - '0');
		str++;
	}
	return (str);
}

static const char	*do_frac(const char *str, double *frac_part, double *div)
{
	str++;
	while (ft_isdigit((unsigned int)*str))
	{
		*frac_part = *frac_part * 10 + (*str - '0');
		*div *= 10;
		str++;
	}
	return (str);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

double	ft_strtod(const char *str, char **endptr)
{
	double	int_part;
	double	frac_part;
	double	div;
	int		sign;
	int		i;

	int_part = 0;
	frac_part = 0;
	div = 1;
	sign = 1;
	i = 0;
	while (ft_isspace((unsigned char)*str) && ++i)
		str++;
	if (*str == '-')
		sign = -1;
	if ((*str == '-' || *str == '+') && ++i)
		str++;
	str = do_int(str, &int_part);
	if (*str == '.' && ++i)
		str = do_frac(str, &frac_part, &div);
	if (endptr != NULL)
		*endptr = (char *)(str - i);
	return (sign * (int_part + frac_part / div));
}
