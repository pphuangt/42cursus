/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:26:27 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/31 08:26:29 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack *stack)
{
	t_arg	*first;
	t_arg	*second;

	if (!stack || !stack->head || stack->head->next == stack->head)
		return ;
	first = stack->head;
	second = first->next;
	if (stack->size == 2)
	{
		stack->head = second;
		stack->last = first;
	}
	else
	{
		first->next = second->next;
		first->next->prev = first;
		second->next = first;
		first->prev = second;
		stack->head = second;
		stack->head->prev = stack->last;
		stack->last->next = stack->head;
	}
}

static void	simul_swap(t_stacks *stacks)
{
	swap(stacks->a);
	swap(stacks->b);
}

void	swap_a(t_stacks *stacks, t_cmds *cmds)
{
	swap(stacks->a);
	if (cmd_append(cmds, sa) < 0)
	{
		free_stacks(stacks);
		free_cmds(cmds);
		exit(255);
	}
}

void	swap_b(t_stacks *stacks, t_cmds *cmds)
{
	swap(stacks->b);
	if (cmd_append(cmds, sb) < 0)
	{
		free_stacks(stacks);
		free_cmds(cmds);
		exit(255);
	}
}

void	swap_ab(t_stacks *stacks, t_cmds *cmds)
{
	simul_swap(stacks);
	if (cmd_append(cmds, sb) < 0)
	{
		free_stacks(stacks);
		free_cmds(cmds);
		exit(255);
	}
}
