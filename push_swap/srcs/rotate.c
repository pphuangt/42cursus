/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:28:09 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/31 08:28:13 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_stack *stack)
{
	if (!stack->head || stack->head == stack->last)
		return ;
	stack->last->next = stack->head;
	stack->head->prev = stack->last;
	stack->last = stack->head;
	stack->head = stack->head->next;
	stack->last->next = stack->head;
	stack->head->prev = stack->last;
}

static void	simul_rotate(t_stacks *stacks)
{
	rotate(stacks->a);
	rotate(stacks->b);
}

void	rotate_a(t_stacks *stacks, t_cmds *cmds)
{
	rotate(stacks->a);
	if (cmd_append(cmds, ra) < 0)
	{
		free_stacks(stacks);
		free_cmds(cmds);
		exit(255);
	}
}

void	rotate_b(t_stacks *stacks, t_cmds *cmds)
{
	rotate(stacks->b);
	if (cmd_append(cmds, rb) < 0)
	{
		free_stacks(stacks);
		free_cmds(cmds);
		exit(255);
	}
}

void	rotate_ab(t_stacks *stacks, t_cmds *cmds)
{
	simul_rotate(stacks);
	if (cmd_append(cmds, rr) < 0)
	{
		free_stacks(stacks);
		free_cmds(cmds);
		exit(255);
	}
}
