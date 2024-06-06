/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:33:01 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/10 18:33:27 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	base_a(t_stacks *stacks, t_cmds *cmds, size_t size)
{
	if (size == 1)
		return ;
	else if (size == 2)
		swap_a(stacks, cmds);
	else if (size == 3)
	{
		if (stacks->a->head->index > stacks->a->head->next->index)
			swap_a(stacks, cmds);
		if (is_sort(stacks->a, size))
			return ;
		rotate_a(stacks, cmds);
		swap_a(stacks, cmds);
		r_rotate_a(stacks, cmds);
		if (stacks->a->head->index > stacks->a->head->next->index)
			swap_a(stacks, cmds);
	}
}

void	partitions_a(t_chunk *chunk, t_stacks *stacks, t_cmds *cmds, size_t i)
{
	t_stack		*a;
	t_stack		*b;

	a = stacks->a;
	b = stacks->b;
	chunk->size_p = chunk->size_1 + chunk->size_2;
	while (chunk->size_p > 0)
	{
		if (a->head->index >= chunk->pivot_2)
		{
			rotate_a(stacks, cmds);
			if (i != 0)
				++(chunk->n_ra);
		}
		else if ((chunk->size_p)--)
		{
			push_b(stacks, cmds);
			if (i != 0 && b->head->index >= chunk->pivot_1 && ++(chunk->n_rb))
				rotate_b(stacks, cmds);
			else if (i == 0 && b->head && b->head->index < chunk->pivot_1
				&& b->head->next->index >= chunk->pivot_1)
				rotate_b(stacks, cmds);
		}
	}
}

void	chunk_a(t_stacks *stacks, t_cmds *cmds, size_t size, size_t i)
{
	t_chunk		chunk;

	if (is_sort(stacks->a, size))
		return ;
	if (size <= 3)
		return (base_a(stacks, cmds, size));
	set_pivot(&chunk, stacks->a, size);
	chunk.n_ra = 0;
	chunk.n_rb = 0;
	partitions_a(&chunk, stacks, cmds, i);
	to_top(&chunk, stacks, cmds);
	chunk_a(stacks, cmds, chunk.size_3, 1);
	chunk_b(stacks, cmds, chunk.size_2, 1);
	chunk_b(stacks, cmds, chunk.size_1, i);
}

void	sort_chunk(t_stacks *stacks, t_cmds *cmds)
{
	chunk_a(stacks, cmds, stacks->a->size, 0);
}
