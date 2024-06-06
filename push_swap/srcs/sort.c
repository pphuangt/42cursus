/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:05:01 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/10 16:05:13 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_stacks *stacks, t_cmds *cmds)
{
	size_t	a;
	size_t	b;
	size_t	c;

	a = stacks->a->head->index;
	b = stacks->a->head->next->index;
	c = stacks->a->head->next->next->index;
	if (c > a && c < b)
	{
		swap_a(stacks, cmds);
		rotate_a(stacks, cmds);
	}
	else if (a > b && a < c)
		swap_a(stacks, cmds);
	else if (a < b && a > c)
		r_rotate_a(stacks, cmds);
	else if (c > b && c < a)
		rotate_a(stacks, cmds);
	else
	{
		swap_a(stacks, cmds);
		r_rotate_a(stacks, cmds);
	}
}

void	sort(t_stacks *stacks)
{
	t_cmds	cmds;

	set_index(stacks->a);
	init_cmds(&cmds);
	if (is_sort(stacks->a, stacks->a->size))
	{
		free_cmds(&cmds);
		free_stacks(stacks);
		return ;
	}
	if (stacks->a->size == 2)
		swap_a(stacks, &cmds);
	else if (stacks->a->size == 3)
		sort_three(stacks, &cmds);
	else
		sort_chunk(stacks, &cmds);
	analyze_cmds(&cmds);
	print_cmds(stacks, &cmds);
	free_cmds(&cmds);
	free_stacks(stacks);
}
