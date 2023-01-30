/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:19:49 by tbelleng          #+#    #+#             */
/*   Updated: 2023/01/30 13:18:15 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        printf("PID child equal %d.\n", pid);
        usleep(1000000); // Attendre 1 seconde.
        printf("child over !\n");
    }
    else if (pid > 0)
    {
        printf("parent and PID child is %d.\n", pid);
        printf("parent ove !\n");
    }
    return (0);
}