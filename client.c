/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:46:01 by ngaurama          #+#    #+#             */
/*   Updated: 2024/12/13 16:15:08 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	g_receiver = 0;

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	i = 0;

	(void)info;
	(void)context;
	g_receiver = 1;
	if (signum == SIGUSR2)
		i++;
	else if (signum == SIGUSR1)
		ft_printf("Number of bytes received: %d\n", i / 8);
}

int	char_to_bin(char c, int pid)
{
	int	itr;
	int	bit_index;

	bit_index = 7;
	while (bit_index >= 0)
	{
		itr = 0;
		if ((c >> bit_index) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_receiver == 0)
		{
			if (itr == 50)
			{
				write(2, "No response from server.\n", 25);
				exit(EXIT_FAILURE);
			}
			itr++;
			usleep(100);
		}
		g_receiver = 0;
		bit_index--;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	int					pid;
	int					byte_index;

	byte_index = 0;
	if (argc != 3)
		return (write(2, "Usage: ./client <PID> <string>\n", 31), 1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (write(2, "Invalid PID.\n", 13), 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (argv[2][byte_index] != '\0')
	{
		if (char_to_bin(argv[2][byte_index], pid) != 0)
			return (write(2, "Error sending character.\n", 25), 1);
		byte_index++;
	}
	char_to_bin('\0', pid);
	return (0);
}
