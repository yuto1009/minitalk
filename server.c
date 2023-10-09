/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutoendo <yutoendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:55:59 by yuendo            #+#    #+#             */
/*   Updated: 2023/10/09 18:35:15 by yutoendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

pid_t get_newest_pid(pid_t current_pid, siginfo_t *info)
{
	if (current_pid != info->si_pid)
	{
		return info->si_pid;
	}
	return current_pid;
}

void sigaction_handler(int signal, siginfo_t *info, void *ucontext)
{
	static pid_t client_pid;
	static char	character;
	static int	bits_received;

	(void)ucontext;
	if (client_pid != get_newest_pid(client_pid, info))
	{
		client_pid = info->si_pid;
		character = RESET;
		bits_received = RESET;
	}
	if (signal == SIGUSR1)
		character |= (0 << bits_received);
	else if (signal == SIGUSR2)
		character |= (1 << bits_received);
	bits_received++;
	if (bits_received == 8)
	{
		write(1, &character, 1);
		character = RESET;
		bits_received = RESET;
		usleep(500);
		kill(client_pid, SIGUSR1);	
	}
	// usleep(300);
	// kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction sa;

	sa.sa_sigaction = sigaction_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
