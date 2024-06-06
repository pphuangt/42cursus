/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:11:58 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/27 16:12:05 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	print_cmd(t_write cmd)
{
	if (cmd == sa)
		return (ft_printf("sa\n"));
	else if (cmd == sb)
		return (ft_printf("sb\n"));
	else if (cmd == ss)
		return (ft_printf("ss\n"));
	else if (cmd == pa)
		return (ft_printf("pa\n"));
	else if (cmd == pb)
		return (ft_printf("pb\n"));
	else if (cmd == ra)
		return (ft_printf("ra\n"));
	else if (cmd == rb)
		return (ft_printf("rb\n"));
	else if (cmd == rr)
		return (ft_printf("rr\n"));
	else if (cmd == rra)
		return (ft_printf("rra\n"));
	else if (cmd == rrb)
		return (ft_printf("rrb\n"));
	else
		return (ft_printf("rrr\n"));
}

void	print_cmds(t_stacks *stacks, t_cmds *cmds)
{
	t_cmd	*cur;

	cur = cmds->head;
	while (cur)
	{
		if (print_cmd(cur->data) < 0)
		{
			free_cmds(cmds);
			free_stacks(stacks);
			exit(255);
		}
		cur = cur->next;
	}
}

void	ft_printf_arg(t_stack *stack)
{
	t_arg	*head;
	t_arg	*tmp;
	size_t	i;

	if (!stack)
	{
		printf("\n");
		return ;
	}
	head = stack->head;
	i = 0;
	while (i < stack->size)
	{
		printf("%zu", head->index);
		printf(" ");
		tmp = head->next;
		head = tmp;
		i++;
	}
	printf("\n");
}
