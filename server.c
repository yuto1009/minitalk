/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutoendo <yutoendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:55:59 by yuendo            #+#    #+#             */
/*   Updated: 2023/10/03 22:51:46 by yutoendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char g_character = 0;
int g_bits_received = 0;

void signal_handler(int signal)
{
    if (signal == SIGUSR1)
        g_character |= (0 << g_bits_received);
    else if (signal == SIGUSR2)
        g_character |= (1 << g_bits_received);
    g_bits_received++;

    if (g_bits_received == 8)
    {
        write(1, &g_character, 1);
        g_character = 0;
        g_bits_received = 0;
    }
}

int main(void)
{
    ft_printf("Server PID: %d\n", getpid());
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    while (1)
        pause();
    return (0);
}