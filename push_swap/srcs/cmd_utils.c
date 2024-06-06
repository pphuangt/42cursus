/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:13:50 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/10 16:13:59 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_cmds(t_cmds *cmds)
{
	cmds->head = NULL;
	cmds->last = NULL;
}

ssize_t	cmd_append(t_cmds *cmds, t_write cmd)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (-1);
	new->data = cmd;
	new->next = NULL;
	if (!cmds->head)
	{
		cmds->head = new;
		cmds->last = new;
	}
	else
	{
		cmds->last->next = new;
		cmds->last = new;
	}
	return (1);
}

void	free_cmds(t_cmds *cmds)
{
	t_cmd	*cur;
	t_cmd	*next;

	if (!cmds || !cmds->head)
		return ;
	cur = cmds->head;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void	rm_cmd(t_cmds *cmds, t_cmd *rm)
{
	t_cmd	*prev;
	t_cmd	*cur;

	cur = cmds->head;
	if (rm == cur)
	{
		cmds->head = cur->next;
		free(cur);
		return ;
	}
	prev = cur;
	cur = cur->next;
	while (cur)
	{
		if (rm == cur)
		{
			prev->next = cur->next;
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
