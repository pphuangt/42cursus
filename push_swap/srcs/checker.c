/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:45:30 by pphuangt          #+#    #+#             */
/*   Updated: 2024/02/14 12:45:33 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	map_cmd(t_stacks *stacks, t_cmds *cmds, char *cmd)
{
	if (!ft_strncmp(cmd, "sa\n", 3))
		swap_a(stacks, cmds);
	else if (!ft_strncmp(cmd, "sb\n", 3))
		swap_b(stacks, cmds);
	else if (!ft_strncmp(cmd, "ss\n", 3))
		swap_ab(stacks, cmds);
	else if (!ft_strncmp(cmd, "pa\n", 3))
		push_a(stacks, cmds);
	else if (!ft_strncmp(cmd, "pb\n", 3))
		push_b(stacks, cmds);
	else if (!ft_strncmp(cmd, "ra\n", 3))
		rotate_a(stacks, cmds);
	else if (!ft_strncmp(cmd, "rb\n", 3))
		rotate_b(stacks, cmds);
	else if (!ft_strncmp(cmd, "rr\n", 3))
		rotate_ab(stacks, cmds);
	else if (!ft_strncmp(cmd, "rra\n", 3))
		r_rotate_a(stacks, cmds);
	else if (!ft_strncmp(cmd, "rrb\n", 3))
		r_rotate_b(stacks, cmds);
	else if (!ft_strncmp(cmd, "rrr\n", 3))
		r_rotate_ab(stacks, cmds);
}

static int	execute_cmd(t_stacks *stacks, t_cmds *cmds, char *cmd)
{
	t_cmd	*tmp;

	tmp = cmds->last;
	map_cmd(stacks, cmds, cmd);
	if (tmp == cmds->last)
	{
		return (0);
	}
	return (1);
}

static void	parsing_cmd(t_stacks *stacks)
{
	t_cmds	cmds;
	char	*line;

	init_cmds(&cmds);
	line = get_next_line(STD_FD);
	while (line)
	{
		if (!execute_cmd(stacks, &cmds, line))
		{
			ft_putstr_fd("Error\n", 2);
			free_stacks(stacks);
			free(line);
			free_cmds(&cmds);
			exit(1);
		}
		free(line);
		line = get_next_line(STD_FD);
	}
	if (is_sort(stacks->a, stacks->a->size) && stacks->b->size == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	free_stacks(stacks);
	free(line);
	free_cmds(&cmds);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	t_arg		*tmp;
	int			i;

	if (argc == 1)
		exit(0);
	if (init_stacks(&stacks) < 0)
		exit(255);
	i = 1;
	while (i < argc)
	{
		tmp = stacks.a->last;
		if (set_arg(&stacks, argv[i++]) < 0 || tmp == stacks.a->last)
		{
			ft_putstr_fd("Error\n", 2);
			free_stacks(&stacks);
			exit(1);
		}
	}
	set_index(stacks.a);
	parsing_cmd(&stacks);
	exit(0);
}
