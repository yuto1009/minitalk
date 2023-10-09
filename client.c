/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutoendo <yutoendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:55:56 by yuendo            #+#    #+#             */
/*   Updated: 2023/10/09 22:04:00 by yutoendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t ack_received = NOT_RECEIVED;

static void    send_character(int pid, char c)
{
    int    i;

    i = 0;
    while (i < 8 && ack_received == NOT_RECEIVED)
    {
        if ((c >> i) & 1)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        i++;
        usleep(200);
    }
    alarm(5);
    usleep(300);
    alarm(RESET);
}

void ack_handler(int signal)
{
    (void)signal;
    ack_received = RECEIVED;
}

void timeout_handler(int signal)
{
    (void)signal;
    ft_printf("Timeout Error\n");
    exit(EXIT_FAILURE);
}

void input_error_exit()
{
    ft_printf("Usage: ./client [SERVER_PID] [STRING]\n");
    exit(1);
}

int    main(int argc, char **argv)
{
    char    *message;
    struct sigaction sa;
    struct sigaction sa_alarm;

    if (argc != 3)
        input_error_exit();
    sa.sa_handler = ack_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    sa_alarm.sa_handler = timeout_handler;
    sigemptyset(&sa_alarm.sa_mask);
    sa_alarm.sa_flags = 0;
    sigaction(SIGALRM, &sa_alarm, NULL);
    message = argv[2];
    while (*message)
    {
        send_character(ft_atoi(argv[1]), *message);
        ack_received = NOT_RECEIVED;
        message++;
    }
    return (0);
}