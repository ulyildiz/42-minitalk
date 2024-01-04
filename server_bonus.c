/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:37:58 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/01/04 19:27:07 by ulyildiz         ###   ########.fr       */
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

static pid_t	client_pid(int *flag, pid_t c_pid, int signal, int i)
{
	if (signal == SIGUSR1)
		c_pid |= (1 << *flag);
	if (i == 1)
	{
		kill(c_pid, SIGUSR1);
		*flag = 0;
		c_pid = 0;
	}
	return (c_pid);
}

static void	sigusr_handler(int signal)
{
	static int		i = 0;
	static char		c = 0;
	static int		flag = 0;
	static pid_t	c_pid = 0;

	if (flag < 32)
	{
		c_pid = client_pid(&flag, c_pid, signal, 0);
		flag++;
	}
	else
	{
		if (signal == SIGUSR1)
			c |= (1 << i);
		if (++i == 8)
		{
			write (1, &c, 1);
			if (c == '\0')
				c_pid = client_pid(&flag, c_pid, signal, 1);
			i = 0;
			c = 0;
		}
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
		write (1, "Please, just type \"./server_bonus\".\n", 36);
		return (1);
	}
	return (0);
}
