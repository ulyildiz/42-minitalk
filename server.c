/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:37:58 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/01/04 19:26:50 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void	put_pid(pid_t pid)
{
	if (pid >= 10)
		put_pid(pid / 10);
	write (1, &"0123456789"[pid % 10], 1);
}

static void	sigusr_handler(int signal)
{
	static int	i = 0;
	static char	c = 0;

	if (signal == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		write (1, &c, 1);
		i = 0;
		c = 0;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	(void)argv;
	if (argc == 1)
	{
		write (1, "Server PID: ", 12);
		put_pid(pid = getpid());
		write(1, "\n", 1);
		signal(SIGUSR1, sigusr_handler);
		signal(SIGUSR2, sigusr_handler);
		while (1)
			pause();
	}
	else
	{
		write (1, "Please, just type \"./server\".\n", 30);
		return (1);
	}
	return (0);
}
