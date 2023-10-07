/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuendo <yuendo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:55:56 by yuendo            #+#    #+#             */
/*   Updated: 2023/10/07 16:35:24 by yuendo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_character(int pid, char c)
{
    int i;

    i = 0;
    while (i < 8)
    {
        if ((c >> i) & 1)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        i++;
        usleep(200);
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        ft_printf("Usage: ./client [SERVER_PID] [STRING]\n");
        exit(1);
    }

    int pid = atoi(argv[1]);
    char *message = argv[2];

    while (*message)
    {
        send_character(pid, *message);
        message++;
    }

    return (0);
}