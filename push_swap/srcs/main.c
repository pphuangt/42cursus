/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:25:06 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/13 16:25:07 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	t_arg		*tmp;
	int			i;

	if (argc == 1)
		exit(0);
	if (init_stacks(&stacks) < 0)
		exit(255);
	i = 1;
	while (i < argc)
	{
		tmp = stacks.a->last;
		if (set_arg(&stacks, argv[i++]) < 0 || tmp == stacks.a->last)
		{
			ft_putstr_fd("Error\n", 2);
			free_stacks(&stacks);
			exit(1);
		}
	}
	if (stacks.a->head)
		sort(&stacks);
	exit(0);
}
