/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:16:37 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/11 14:16:46 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	to_top(t_chunk *chunk, t_stacks *stacks, t_cmds *cmds)
{
	while (chunk->n_ra > 0 && chunk->n_rb > 0)
	{
		r_rotate_ab(stacks, cmds);
		chunk->n_ra = chunk->n_ra - 1;
		chunk->n_rb = chunk->n_rb - 1;
	}
	while (chunk->n_ra > 0)
	{
		r_rotate_a(stacks, cmds);
		chunk->n_ra = chunk->n_ra - 1;
	}
	while (chunk->n_rb > 0)
	{
		r_rotate_b(stacks, cmds);
		chunk->n_rb = chunk->n_rb - 1;
	}
}

void	set_pivot(t_chunk *chunk, t_stack *stack, size_t size)
{
	t_arg	*cur;
	size_t	l;
	size_t	r;

	cur = stack->head;
	l = stack->head->index;
	r = stack->head->index;
	while (size > 0)
	{
		if (cur->index < l)
			l = cur->index;
		if (cur->index > r)
			r = cur->index;
		cur = cur->next;
		size--;
	}
	chunk->pivot_1 = l + (r - l + 1) / 3;
	chunk->pivot_2 = r - (r - l) / 3;
	chunk->size_1 = chunk->pivot_1 - l;
	chunk->size_2 = chunk->pivot_2 - chunk->pivot_1;
	chunk->size_3 = r + 1 - chunk->pivot_2;
}

void	handle_one(t_chunk *chunk, t_stacks *stacks, size_t *n)
{
	t_stack	*a;

	a = stacks->a;
	if (a->head->index >= chunk->pivot_2)
		chunk->size_3 = chunk->size_3 - 1;
	else
		chunk->size_2 = chunk->size_2 - 1;
	*n = *n - 1;
}

void	handle_two(t_chunk *chunk, t_stacks *stacks, t_cmds *cmds, size_t *n)
{
	t_stack	*b;

	b = stacks->b;
	if (b->head->index >= chunk->pivot_2)
		chunk->size_3 = chunk->size_3 - 1;
	else
		chunk->size_2 = chunk->size_2 - 1;
	push_a(stacks, cmds);
	swap_a(stacks, cmds);
	*n = *n - 1;
	(chunk->size_p)--;
}

void	handle_sort(t_chunk *chunk, t_stacks *stacks, t_cmds *cmds, size_t *n)
{
	t_stack	*a;
	t_stack	*b;

	a = stacks->a;
	b = stacks->b;
	if (b->head->index + 1 == *n && a->head->next->index == *n
		&& chunk->size_p >= 2)
		handle_two(chunk, stacks, cmds, n);
	if (a->head->index + 1 == *n && a->head->next->index == *n)
		handle_one(chunk, stacks, n);
	else if (a->head->index < chunk->pivot_2 && ++(chunk->n_ra))
		rotate_a(stacks, cmds);
}
