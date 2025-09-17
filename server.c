/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:55:20 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/06 17:18:22 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	pid = 0;
	static char	c = 0;
	static int	i = 0;

	(void)context;
	if (pid == 0)
		pid = info->si_pid;
	if (signum == SIGUSR1)
		c = (c << 1) | 1;
	else if (signum == SIGUSR2)
		c = c << 1;
	i++;
	if (i == 8)
	{
		i = 0;
		if (c == '\0')
		{
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
	}
	kill(pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write(2, "Error setting SIGUSR1 handler", 29);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Error setting SIGUSR2 handler", 29);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}
