/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:14:40 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/27 16:14:42 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_duplicate(t_stack *stack, int num)
{
	t_arg	*tmp;
	size_t	i;

	tmp = stack->head;
	i = 0;
	if (!tmp)
		return (0);
	while (i < stack->size)
	{
		if (tmp->data == num)
			return (1);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

int	set_arg(t_stacks *stacks, char *arg)
{
	int		i;
	int		num;
	int		sign;

	i = 0;
	while (arg[i] != '\0')
	{
		num = 0;
		if (is_format(arg[i]) < 0)
			return (-1);
		while (arg[i] == ' ')
			i++;
		if (is_sign(arg, &i, &sign) < 0)
			return (-1);
		while (ft_isdigit(arg[i]))
		{
			if (is_overflow(num, sign, arg[i]))
				return (-1);
			num = num * 10 + sign * (arg[i++] - '0');
		}
		if ((i > 0 && ft_isdigit(arg[i - 1])) && !stack_append(stacks, num))
			return (-1);
	}
	return (1);
}

void	set_min_max(t_stack *stack, size_t index)
{
	if (stack->size == 1)
	{
		stack->max = index;
		stack->min = index;
	}
	else if (index > stack->max)
		stack->max = index;
	else if (index < stack->min)
		stack->min = index;
}

void	update_min_max(t_stack *stack)
{
	t_arg	*head;
	size_t	i;

	head = stack->head;
	if (!head)
		return ;
	stack->max = head->index;
	stack->min = head->index;
	i = 0;
	while (i < stack->size)
	{
		set_min_max(stack, head->index);
		head = head->next;
		i++;
	}
}

void	set_index(t_stack *stack_a)
{
	t_arg	*head;
	t_arg	*tmp;
	size_t	res;
	size_t	i;
	size_t	j;

	head = stack_a->head;
	i = 0;
	while (i++ < stack_a->size)
	{
		tmp = stack_a->head;
		res = 0;
		j = 0;
		while (j++ < stack_a->size)
		{
			if (tmp->data < head->data)
				res++;
			tmp = tmp->next;
		}
		head->index = res;
		set_min_max(stack_a, res);
		head = head->next;
	}
}
