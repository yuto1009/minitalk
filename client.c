/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuendo <yuendo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:55:56 by yuendo            #+#    #+#             */
/*   Updated: 2023/09/29 14:53:50 by yuendo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void send_character(int pid, char c)
{
    for (int i = 0; i < 8; i++)
    {
        if ((c >> i) & 1)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        usleep(100);
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