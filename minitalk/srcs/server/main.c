/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:31:13 by pphuangt          #+#    #+#             */
/*   Updated: 2024/03/20 20:31:20 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static char	c = 0;
	static char	i = 0;

	(void)context;
	if (signum == SIGUSR2)
		c = c | (1 << i);
	i++;
	if (i == 8)
	{
		if (write(1, &c, 1) < 0)
		{
			ft_printf("\nError: from write function\n");
			exit(1);
		}
		c = 0;
		i = 0;
		kill(info->si_pid, SIGUSR2);
	}
	else
		kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	int					server_pid;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) < 0)
	{
		ft_putstr_fd("Error: from sigemptyset\n", 2);
		return (0);
	}
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error: can't initialize signal handler\n", 2);
		return (0);
	}
	server_pid = getpid();
	ft_printf("pid: %d\n", server_pid);
	while (1)
	{
	}
	return (0);
}
