/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:50:17 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/14 15:50:27 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sort(t_stack *stack, size_t r)
{
	t_arg	*head;
	size_t	i;

	head = stack->head;
	if (!head || stack->head == stack->last)
	{
		return (1);
	}
	i = 0;
	while (i < (r - 1))
	{
		if (head->index > head->next->index)
			return (0);
		head = head->next;
		i++;
	}
	return (1);
}

int	is_reverse_sort(t_stack *stack, size_t r)
{
	t_arg	*head;
	size_t	i;

	head = stack->head;
	if (!head || stack->head == stack->last)
		return (1);
	i = 0;
	while (i < (r - 1))
	{
		if (head->index < head->next->index)
			return (0);
		head = head->next;
		i++;
	}
	return (1);
}
