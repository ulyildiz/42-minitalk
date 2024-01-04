/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:37:53 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/01/04 19:28:45 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static int	convert_pid(char *pid)
{
	pid_t	res;
	size_t	i;

	i = 0;
	while (pid[i] != '\0')
	{
		if (!('0' <= pid[i] && pid[i] <= '9'))
		{
			write (1, "Server's PID have to contain only numbers.\n", 43);
			exit (1);
		}
		i++;
	}
	res = 0;
	while (*pid != '\0')
		res = (res * 10) + (*(pid++) - '0');
	return (res);
}

static void	sending_signal(char letter, pid_t *pid)
{
	int	i;

	if (kill(*pid, 0) != 0)
	{
		write (1, "Connection lost.", 16);
		exit(1);
	}
	i = 0;
	while (i < 8)
	{
		if ((letter & (1 << i)) != 0)
			kill(*pid, SIGUSR1);
		else
			kill(*pid, SIGUSR2);
		usleep(125);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	pid;
	size_t	i;

	if (argc != 3)
	{
		write (1, "Please, type as \"./client ", 27);
		write (1, "<server_pid_number> <string>\".\n", 31);
		return (1);
	}
	i = 0;
	pid = convert_pid(argv[1]);
	if (kill(pid, 0) != 0)
	{
		write (1, "Invalid PID.\n", 13);
		exit(1);
	}
	while (argv[2][i] != '\0')
		sending_signal(argv[2][i++], &pid);
	sending_signal('\n', &pid);
	return (0);
}
