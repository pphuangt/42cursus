/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:23 by pphuangt          #+#    #+#             */
/*   Updated: 2024/04/30 18:00:25 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <limits.h>
# include "ft_printf.h"

typedef enum s_status
{
	SEND,
	RECEIVE
}	t_status;

typedef struct s_var
{
	char			c;
	unsigned char	i;
	size_t			count;
	t_status		status;
}	t_var;

#endif
