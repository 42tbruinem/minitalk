/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/28 12:34:37 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/05/28 15:03:29 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include "server.h"
#include <sys/types.h>

t_message	g_message;

#define BIGGEST_NUMBER_REPRESENTATION "2147483647"

void	receive(int sig)
{
	bool	bit = (sig == SIGUSR2);

//	printf("RECEIVED: %d\n", (sig == SIGUSR2));
	g_message.bits |= (int)bit << (7 - g_message.bitcounter);
	g_message.bitcounter++;
	if (g_message.bitcounter == (sizeof(char) * 8))
	{
		write(STDIN_FILENO, &g_message.bits, sizeof(char));
		g_message.bits = 0;
		g_message.bitcounter = 0;
	}
}

bool	init(void)
{
	sigset_t			sigset;
	struct sigaction	action;

	g_message.bitcounter = 0;
	g_message.bits = 0;
	action.sa_handler = receive;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &action, NULL) == -1)
		return (false);
	sigdelset(&action.sa_mask, SIGUSR2);
	sigaddset(&action.sa_mask, SIGUSR1);
	if (sigaction(SIGUSR2, &action, NULL) == -1)
		return (false);
	return (true);
}

void	print_pid(pid_t pid)
{
	char	buf[sizeof(BIGGEST_NUMBER_REPRESENTATION)];
	int		size;

	size = sizeof(BIGGEST_NUMBER_REPRESENTATION) - 1;
	buf[size] = '\n';
	while (pid)
	{
		size--;
		buf[size] = '0' + (pid % 10);
		pid /= 10;
	}
	write(STDIN_FILENO, buf + size, sizeof(BIGGEST_NUMBER_REPRESENTATION) - size);
}

int main(void)
{
	print_pid(getpid());
	if (!init())
		return (1);
	while (42)
		pause();
	return (0);
}
