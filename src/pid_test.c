/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:19:49 by tbelleng          #+#    #+#             */
/*   Updated: 2023/01/25 16:23:45 by tbelleng         ###   ########.fr       */
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
        printf("Fils : Je suis le fils, mon pid interne est %d.\n", pid);
        usleep(1000000); // Attendre 1 seconde.
        printf("Fils : Termine !\n");
    }
    else if (pid > 0)
    {
        printf("Pere : Je suis le pere, le pid de mon fils est %d.\n", pid);
        printf("Pere : Termine !\n");
    }
    return (0);
}