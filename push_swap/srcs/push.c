/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 08:29:15 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/31 08:29:16 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	pop_from_source(t_stack *src)
{
	t_arg	*tmp;

	if (!src->head)
		return ;
	tmp = src->head;
	src->head = src->head->next;
	if (src->head == tmp)
	{
		src->head = NULL;
		src->last = NULL;
	}
	else
	{
		src->last->next = src->head;
		src->head->prev = src->last;
	}
	src->size--;
	if (src->min == tmp->index || src->max == tmp->index)
		update_min_max(src);
}

static void	push_to_destination(t_stack *dst, t_arg *tmp)
{
	tmp->next = dst->head;
	if (!dst->head)
	{
		dst->head = tmp;
		dst->last = tmp;
		tmp->next = tmp;
		tmp->prev = tmp;
	}
	else
	{
		dst->head = tmp;
		tmp->prev = dst->last;
		dst->last->next = tmp;
		tmp->next->prev = tmp;
	}
	dst->size++;
	set_min_max(dst, tmp->index);
}

static void	push(t_stack *src, t_stack *dst)
{
	t_arg	*tmp;

	if (!src->head)
		return ;
	tmp = src->head;
	pop_from_source(src);
	push_to_destination(dst, tmp);
}

void	push_a(t_stacks *stacks, t_cmds *cmds)
{
	push(stacks->b, stacks->a);
	if (cmd_append(cmds, pa) < 0)
	{
		free_stacks(stacks);
		free_cmds(cmds);
		exit(255);
	}
}

void	push_b(t_stacks *stacks, t_cmds *cmds)
{
	push(stacks->a, stacks->b);
	if (cmd_append(cmds, pb) < 0)
	{
		free_stacks(stacks);
		free_cmds(cmds);
		exit(255);
	}
}
