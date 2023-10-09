/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutoendo <yutoendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:55:56 by yuendo            #+#    #+#             */
/*   Updated: 2023/10/09 20:03:28 by yutoendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t ack_received = NOT_RECEIVED;

static void	send_character(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i++;
		usleep(350);
		// alarm(5);
		// while (ack_received == NOT_RECEIVED)
		// pause();
		// alarm(RESET);
		// ack_received = NOT_RECEIVED;
	}
	usleep(3250);
	alarm(5);
	while (ack_received == NOT_RECEIVED)
		pause();
	alarm(RESET);
	ack_received = NOT_RECEIVED;
}

void ack_handler(int signal)
{
	(void)signal;
	ack_received = RECEIVED;
	// ft_printf("aaa\n");
}

void timeout_handler(int signal)
{
	(void)signal;
	ft_printf("Timeout Error\n");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	int		server_pid;
	char	*message;
	struct sigaction sa;
	struct sigaction sa_alarm;

	if (argc != 3)
	{
		ft_printf("Usage: ./client [SERVER_PID] [STRING]\n");
		exit(1);
	}
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sa_alarm.sa_handler = timeout_handler;
	sigaction(SIGALRM, &sa_alarm, NULL);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	while (*message)
	{
		send_character(server_pid, *message);
		message++;
	}
	return (0);
}
