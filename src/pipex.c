/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:24:13 by tbelleng          #+#    #+#             */
/*   Updated: 2023/01/30 15:08:29 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


int     main(int ac, char **av, char **envp)
{
	pid_t child;
	pid_t child2;
	pid_t res;
	pid_t res2;
	int status;
	int status2;
	int file[2];
	int fd_in;
	(void)ac;
	(void)av;
	
	printf("forking...\n");
	fd_in = 0;
	fd_in = open("test_in.txt", O_RDONLY);
	if (pipe(file) == -1)
		return (0);
	child = fork();
	child2 = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		command_exec(envp, fd_in, file);
	}
	if (child2 == 0)
	{
		command_exec2(envp);
	}
	else if (child > 0)
	{
		res = waitpid(child, &status, 0);
		res2 = waitpid(child2, &status2, 0);
		if (WIFEXITED(status) && WIFEXITED(status2))
		{
			close(fd_in);
			printf("succes\n");
		}
        else
            printf("interrupted...");
	}
	printf("Process completed\n");
	return (0);
}