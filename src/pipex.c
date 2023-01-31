/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:24:13 by tbelleng          #+#    #+#             */
/*   Updated: 2023/01/31 22:40:08 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


int     main(int ac, char **av, char **envp)
{
	t_pipe	data;
	(void)ac;
	(void)av;
	
	data.envp = envp;
	data.file_in = open(av[1], O_RDONLY);
	if (data.file_in < 0)
		return (0);
	data.file_out = open(av[ac - 1], O_RDWR);
	if (data.file_out < 0)
		return (0);
	if (pipe(&data.pipe[0]) == 0)
		return (0);
	data.child = fork();
	data.child2 = fork();
	if (data.child == -1)
		return (1);
	if (data.child == 0)
	{
		command_exec(&data);
	}
	if (data.child2 == 0)
	{
		command_exec2(&data);
	}
	else if (data.child > 0)
	{
		data.res = waitpid(data.child, &data.status, 0);
		data.res2 = waitpid(data.child2, &data.status2, 0);
		if (WIFEXITED(data.status) && WIFEXITED(data.status2))
		{
			close(data.file_in);
			printf("succes\n");
		}
        else
            printf("interrupted...");
	}
	printf("Process completed\n");
	return (0);
}