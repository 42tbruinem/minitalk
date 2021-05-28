/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/28 14:20:24 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/05/28 15:12:32 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>

pid_t	read_pid(char *str)
{
	pid_t	pid;
	size_t	i;

	pid = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		pid = (pid * 10) + (str[i] - '0');
		i++;
	}
	return (pid);
}

void	send_bit(pid_t server_pid, bool bit)
{
//	printf("SENDING %d TO SERVER WITH PID %d\n", (int)bit, server_pid);
	if (bit)
		kill(server_pid, SIGUSR2);
	else
		kill(server_pid, SIGUSR1);
	usleep(500);
}

void	send_character(pid_t server_pid, char c)
{
	size_t	bit_counter;
	bool	bit;

	bit_counter = 0;
	while (bit_counter < 8)
	{
		send_bit(server_pid, (c >> (7 - bit_counter)) & 1);
		bit_counter++;
	}
//	printf("---\n");
}

void	send_message(pid_t server_pid, char *message)
{
	size_t	i;

	i = 0;
	while (message[i])
	{
		send_character(server_pid, message[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
		return (1);
	server_pid = read_pid(argv[1]);
	send_message(server_pid, argv[2]);
	return (0);
}
