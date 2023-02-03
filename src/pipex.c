/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:24:13 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/03 18:59:11 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int error_occur(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

int     main(int ac, char **av, char **envp)
{
	t_pipe	data;
	(void)ac;
	(void)av;
	

	data.envp = envp;
	if (ac != 5)
		error_occur("not enough arg\n");
	data.file_in = open(av[1], O_RDONLY);
	if (data.file_in < 0)
		error_occur("no in file\n");
	data.file_out = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (data.file_out < 0)
		error_occur("error with out file\n");
	if (pipe(&data.pipe[0]) == -1)
		error_occur("error while pipe creation\n");
	data.child = fork();
	data.child2 = fork();
	if (data.child == -1)
		error_occur("fork failed\n");
	if (data.child2 == -1)
		error_occur("fork failed\n");	
	if (data.child == 0)
		command_exec(&data, ac, av);
	if (data.child2 == 0)
		command_exec2(&data, ac, av);
	close_all(&data);
	printf("DEBUG1\n");
	waitpid(data.child, NULL, 0);
	printf("DEBUG2\n");
	waitpid(data.child2, NULL, 0);
	printf("DEBUG\n");
	/*if (WIFEXITED(data.status) && WIFEXITED(data.status2))
		printf("succes\n");
    else
        error_occur("error during \n");*/
    //free(data.cmd_path);
	printf("Process completed\n");
	return (0);
}