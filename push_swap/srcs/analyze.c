/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:30:28 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/05 19:30:29 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rm_ss(t_cmds *cmds)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = cmds->head;
	if (!cur)
		return ;
	next = cur->next;
	while (next)
	{
		if ((cur->data == sa && next->data == sb)
			|| (cur->data == sb && next->data == sa))
		{
			rm_cmd(cmds, cur);
			next->data = ss;
		}
		cur = next;
		next = next->next;
	}
}

void	rm_rr(t_cmds *cmds)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = cmds->head;
	if (!cur)
		return ;
	next = cur->next;
	while (next)
	{
		if ((cur->data == ra && next->data == rb)
			|| (cur->data == rb && next->data == ra))
		{
			rm_cmd(cmds, cur);
			next->data = rr;
		}
		cur = next;
		next = next->next;
	}
}

void	rm_rotate(t_cmds *cmds)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = cmds->head;
	if (!cur)
		return ;
	next = cur->next;
	while (next)
	{
		if ((cur->data == ra && next->data == rra)
			|| (cur->data == rb && next->data == rrb))
		{
			rm_cmd(cmds, cur);
			cur = next->next;
			rm_cmd(cmds, next);
			if (!cur)
				return ;
			next = cur->next;
		}
		else
		{
			cur = next;
			next = next->next;
		}
	}
}

void	rm_push(t_cmds *cmds)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = cmds->head;
	if (!cur)
		return ;
	next = cur->next;
	while (next)
	{
		if ((cur->data == pa && next->data == pb)
			|| (cur->data == pb && next->data == pa))
		{
			rm_cmd(cmds, cur);
			cur = next->next;
			rm_cmd(cmds, next);
			if (!cur)
				return ;
			next = cur->next;
		}
		else
		{
			cur = next;
			next = next->next;
		}
	}
}

void	analyze_cmds(t_cmds *cmds)
{
	rm_rotate(cmds);
	rm_push(cmds);
	rm_rr(cmds);
	rm_ss(cmds);
}
