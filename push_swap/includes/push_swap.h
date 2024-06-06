/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:20:44 by pphuangt          #+#    #+#             */
/*   Updated: 2024/01/22 16:12:19 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include "ft_printf.h"

typedef enum s_write
{
	sa,
	sb,
	ss,
	pa,
	pb,
	ra,
	rb,
	rr,
	rra,
	rrb,
	rrr
}	t_write;

typedef struct s_cmd
{
	t_write			data;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_cmds
{
	t_cmd	*head;
	t_cmd	*last;
}	t_cmds;

typedef struct s_arg
{
	int				data;
	size_t			index;
	struct s_arg	*next;
	struct s_arg	*prev;
}	t_arg;

typedef struct s_stack
{
	t_arg	*head;
	t_arg	*last;
	size_t	size;
	size_t	max;
	size_t	min;
}	t_stack;

typedef struct s_stacks
{
	t_stack	*a;
	t_stack	*b;
}	t_stacks;

typedef struct s_chunk
{
	size_t	pivot_1;
	size_t	pivot_2;
	size_t	size_1;
	size_t	size_2;
	size_t	size_3;
	size_t	n_ra;
	size_t	n_rb;
	size_t	size_p;
}	t_chunk;

// sort
void	sort(t_stacks *stacks);
int		is_sort(t_stack *stack, size_t r);
int		is_reverse_sort(t_stack *stack, size_t r);
void	sort_chunk(t_stacks *stacks, t_cmds *cmds);

// chunk utils
void	to_top(t_chunk *chunk, t_stacks *stacks, t_cmds *cmds);
void	set_pivot(t_chunk *chunk, t_stack *stack, size_t size);
void	chunk_a(t_stacks *stacks, t_cmds *cmds, size_t size, size_t i);
void	chunk_b(t_stacks *stacks, t_cmds *cmds, size_t size, size_t i);
void	handle_sort(t_chunk *chunk, t_stacks *stacks, t_cmds *cmds, size_t *n);
void	handle_one(t_chunk *chunk, t_stacks *stacks, size_t *n);
void	handle_two(t_chunk *chunk, t_stacks *stacks, t_cmds *cmds, size_t *n);

// analyzie
void	analyze_cmds(t_cmds *cmds);

// command
void	swap_a(t_stacks *stacks, t_cmds *cmds);
void	swap_b(t_stacks *stacks, t_cmds *cmds);
void	swap_ab(t_stacks *stacks, t_cmds *cmds);
void	push_a(t_stacks *stacks, t_cmds *cmds);
void	push_b(t_stacks *stacks, t_cmds *cmds);
void	rotate_a(t_stacks *stacks, t_cmds *cmds);
void	rotate_b(t_stacks *stacks, t_cmds *cmds);
void	rotate_ab(t_stacks *stacks, t_cmds *cmds);
void	r_rotate_a(t_stacks *stacks, t_cmds *cmds);
void	r_rotate_b(t_stacks *stacks, t_cmds *cmds);
void	r_rotate_ab(t_stacks *stacks, t_cmds *cmds);

// stacks utils
int		set_arg(t_stacks *stacks, char *arg);
int		is_duplicate(t_stack *stack, int num);
int		stack_append(t_stacks *stacks, int num);
void	set_min_max(t_stack *stack, size_t index);
void	update_min_max(t_stack *stack);
void	set_index(t_stack *stack_a);
ssize_t	init_stacks(t_stacks *stacks);
void	free_stacks(t_stacks *stacks);
t_arg	*create_t_arg(t_stacks *stacks, int num);

// input utils
int		is_overflow(int num, int sing, char c);
int		is_format(char c);
int		is_sign(char *arg, int *i, int *sign);

// cmds utils
void	init_cmds(t_cmds *cmds);
ssize_t	cmd_append(t_cmds *cmds, t_write cmd);
void	free_cmds(t_cmds *cmds);
void	print_cmds(t_stacks *stacks, t_cmds *cmds);
void	rm_cmd(t_cmds *cmds, t_cmd *rm);

// test
void	ft_printf_arg(t_stack *stack);

#endif
