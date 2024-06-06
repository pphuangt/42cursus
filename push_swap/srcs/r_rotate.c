/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_rotate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:16:48 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/10 16:17:00 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	r_rotate(t_stack *stack)
{
	if (!stack->head || stack->head == stack->last)
		return ;
	stack->last->next = stack->head;
	stack->head->prev = stack->last;
	stack->head = stack->last;
	stack->last = stack->last->prev;
	stack->last->next = stack->head;
	stack->head->prev = stack->last;
}

static void	simul_r_rotate(t_stacks *stacks)
{
	r_rotate(stacks->a);
	r_rotate(stacks->b);
}

void	r_rotate_a(t_stacks *stacks, t_cmds *cmds)
{
	r_rotate(stacks->a);
	if (cmd_append(cmds, rra) < 0)
	{
		free_stacks(stacks);
		free_cmds(cmds);
		exit(255);
	}
}

void	r_rotate_b(t_stacks *stacks, t_cmds *cmds)
{
	r_rotate(stacks->b);
	if (cmd_append(cmds, rrb) < 0)
	{
		free_stacks(stacks);
		free_cmds(cmds);
		exit(255);
	}
}

void	r_rotate_ab(t_stacks *stacks, t_cmds *cmds)
{
	simul_r_rotate(stacks);
	if (cmd_append(cmds, rrr) < 0)
	{
		free_stacks(stacks);
		free_cmds(cmds);
		exit(255);
	}
}
