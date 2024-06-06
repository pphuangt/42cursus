/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:22:30 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/11 15:22:38 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	base_b(t_stacks *stacks, t_cmds *cmds, size_t size)
{
	if (size == 1)
		push_a(stacks, cmds);
	else if (size == 2)
	{
		swap_b(stacks, cmds);
		push_a(stacks, cmds);
		push_a(stacks, cmds);
	}
	else if (size == 3)
	{
		if (stacks->b->head->next->index > stacks->b->head->index)
			swap_b(stacks, cmds);
		push_a(stacks, cmds);
		if (stacks->b->head->next->index > stacks->b->head->index)
			swap_b(stacks, cmds);
		push_a(stacks, cmds);
		if (stacks->a->head->next->index < stacks->a->head->index)
			swap_a(stacks, cmds);
		push_a(stacks, cmds);
	}
}

void	partitions_b(t_chunk *chunk, t_stacks *stacks, t_cmds *cmds, size_t i)
{
	t_stack	*b;
	size_t	n;

	b = stacks->b;
	chunk->size_p = chunk->size_2 + chunk->size_3;
	n = stacks->a->head->index;
	while (chunk->size_p > 0)
	{
		if (b->head->index < chunk->pivot_1)
		{
			rotate_b(stacks, cmds);
			if (i != 0)
				++(chunk->n_rb);
		}
		else
		{
			push_a(stacks, cmds);
			handle_sort(chunk, stacks, cmds, &n);
			(chunk->size_p)--;
		}
	}
}

void	chunk_b(t_stacks *stacks, t_cmds *cmds, size_t size, size_t i)
{
	t_chunk	chunk;

	if (is_reverse_sort(stacks->b, size))
	{
		while (size-- > 0)
			push_a(stacks, cmds);
		return ;
	}
	if (size <= 3)
		return (base_b(stacks, cmds, size));
	set_pivot(&chunk, stacks->b, size);
	chunk.n_ra = 0;
	chunk.n_rb = 0;
	partitions_b(&chunk, stacks, cmds, i);
	chunk_a(stacks, cmds, chunk.size_3, 1);
	to_top(&chunk, stacks, cmds);
	chunk_a(stacks, cmds, chunk.size_2, 1);
	chunk_b(stacks, cmds, chunk.size_1, i);
}
