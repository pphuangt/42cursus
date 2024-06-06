/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:32:00 by pphuangt          #+#    #+#             */
/*   Updated: 2024/03/20 20:32:06 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	g_status = 0;

void	newline_and_acknowledge(int pid, int count)
{
	unsigned char	i;
	unsigned char	bit;

	i = 0;
	while (i < 8)
	{
		bit = ('\n' >> i) & 1;
		i++;
		if (bit == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_status)
		{
		}
		g_status = 0;
	}
	ft_printf("server acknowledge: %d byte\n", count);
}

void	send_message(int pid, char *str)
{
	int				count;
	unsigned int	bit;
	unsigned int	i;
	unsigned char	j;

	count = 0;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		bit = (str[i] >> j) & 1;
		if (++j == 8 && ++i)
			j = 0;
		if (bit == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_status)
		{
		}
		if (g_status == 2)
			count++;
		g_status = 0;
	}
	newline_and_acknowledge(pid, count);
}

void	signal_handler(int signum)
{
	if (signum == SIGUSR2)
		g_status = 2;
	else
		g_status = 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_printf("Please specify only PID and message\n");
		ft_printf("./client [PID] [message]\n");
		return (0);
	}
	sa.sa_handler = signal_handler;
	if (sigemptyset(&sa.sa_mask) < 0)
	{
		ft_putstr_fd("Error: from sigemptyset\n", 2);
		return (0);
	}
	if (sigaction(SIGUSR1, &sa, NULL) < 0
		|| sigaction(SIGUSR2, &sa, NULL) < 0)
	{
		ft_putstr_fd("Error: can't initialize signal handler\n", 2);
		return (0);
	}
	send_message(ft_atoi(argv[1]), argv[2]);
	return (0);
}
