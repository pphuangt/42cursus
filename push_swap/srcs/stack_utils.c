/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:14:53 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/10 16:14:58 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

ssize_t	init_stacks(t_stacks *stacks)
{
	stacks->a = malloc(sizeof(t_stack));
	if (!stacks->a)
		return (-1);
	stacks->b = malloc(sizeof(t_stack));
	if (!stacks->b)
	{
		free(stacks->a);
		return (-1);
	}
	stacks->a->head = NULL;
	stacks->a->last = NULL;
	stacks->a->size = 0;
	stacks->a->max = 0;
	stacks->a->min = 0;
	stacks->b->head = NULL;
	stacks->b->last = NULL;
	stacks->b->size = 0;
	stacks->b->max = 0;
	stacks->b->min = 0;
	return (1);
}

int	stack_append(t_stacks *stacks, int num)
{
	t_arg	*new;

	new = create_t_arg(stacks, num);
	if (is_duplicate(stacks->a, num))
	{
		free(new);
		return (0);
	}
	if (!(stacks->a->head))
	{
		new->prev = new;
		new->next = new;
		stacks->a->head = new;
	}
	else
	{
		new->prev = stacks->a->last;
		new->next = stacks->a->head;
		stacks->a->last->next = new;
		stacks->a->head->prev = new;
	}
	stacks->a->last = new;
	stacks->a->size = stacks->a->size + 1;
	return (1);
}

static void	free_stack(t_stack *stack)
{
	t_arg	*cur;
	t_arg	*next;
	size_t	i;

	if (!stack)
		return ;
	cur = stack->head;
	i = 0;
	while (i++ < stack->size)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void	free_stacks(t_stacks *stacks)
{
	t_stack	*stack;

	stack = stacks->a;
	free_stack(stack);
	free(stack);
	stack = stacks->b;
	free_stack(stack);
	free(stack);
}

t_arg	*create_t_arg(t_stacks *stacks, int num)
{
	t_arg	*new;

	new = (t_arg *)malloc(sizeof(t_arg));
	if (!new)
	{
		free_stacks(stacks);
		exit(255);
	}
	new->data = num;
	new->index = 0;
	return (new);
}
