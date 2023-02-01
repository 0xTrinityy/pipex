/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:24:13 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/01 19:39:18 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


int     main(int ac, char **av, char **envp)
{
	t_pipe	data;
	(void)ac;
	(void)av;
	
	if (ac != 5)
		return (0);
	data.envp = envp;
	data.file_in = open(av[1], O_RDONLY);
	if (data.file_in < 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
        write(2, "\n", 1);
		return (0);
	}
	if (!av[4])
		data.file_out = open("src/file_out.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	else
		data.file_out = open(av[4], O_RDWR | O_CREAT | O_TRUNC);
	if (data.file_out < 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
        write(2, "\n", 1);
		return (0);
	}
	if (pipe(&data.pipe[0]) == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
        write(2, "\n", 1);
        return (0);
    }
	data.child = fork();
	data.child2 = fork();
	if (data.child == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
        write(2, "\n", 1);
		return (0);
	}
	if (data.child2 == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
        write(2, "\n", 1);
		return (0);
	}	
	if (data.child == 0)
	{
		command_exec(&data, ac, av);
	}
	if (data.child2 == 0)
	{
		command_exec2(&data, ac, av);
	}
	else if (data.child > 0)
	{
		data.res = waitpid(data.child, &data.status, 0);
		data.res2 = waitpid(data.child2, &data.status2, 0);
		if (WIFEXITED(data.status) && WIFEXITED(data.status2))
			printf("succes\n");
        else
        {
            write(2, strerror(errno), ft_strlen(strerror(errno)));
            write(2, "\n", 1);
            return (0);
		}
	}
	close(data.pipe[0]);
	close(data.pipe[1]);
	close(data.file_in);
	close(data.file_out);
	printf("Process completed\n");
	return (0);
}