/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuendo <yuendo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:55:59 by yuendo            #+#    #+#             */
/*   Updated: 2023/10/07 17:40:51 by yuendo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void signal_handler(int signal)
{
    static char character;
    static int bits_received;
    
    if (signal == SIGUSR1)
        character |= (0 << bits_received);
    else if (signal == SIGUSR2)
        character |= (1 << bits_received);
    bits_received++;

    if (bits_received == 8)
    {
        write(1, &character, 1);
        character = 0;
        bits_received = 0;
    }
}

int main(void)
{
    struct sigaction sa1;
    struct sigaction sa2;
    
    sa1.sa_handler = signal_handler;
    sa2.sa_handler = signal_handler;
    sigemptyset(&sa1.sa_mask);
    sigemptyset(&sa2.sa_mask);
    sa1.sa_flags =  0;
    sa2.sa_flags =  0;
    // signal(SIGUSR1, signal_handler);
    // signal(SIGUSR2, signal_handler);
    sigaction(SIGUSR1, &sa1, NULL);
    sigaction(SIGUSR2, &sa2, NULL);
    ft_printf("Server PID: %d\n", getpid());
    while (1)
        pause();
    return (0);
}