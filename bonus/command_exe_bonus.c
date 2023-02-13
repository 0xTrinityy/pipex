/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exe_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:53:41 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/13 17:43:50 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	mid_child(t_pipe data, int j, char **argv, char **envp)
{
	dup2(data.pipe[2 * j + 1], 1);
	close(data.pipe[2 * j - 1]);
	dup2(data.pipe[2 * j - 2], 0);
	data.cmd_args = ft_split(argv[j + 2], ' ');
	data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
	if (!data.cmd)
	{
		child_free(&data);
		msg(ERR_CMD);
		exit(1);
	}
	execve(data.cmd, data.cmd_args, envp);
}

void    multiple_cmd(t_pipe data, int argc, char **argv, char **envp)
{
	int     i;
	int     j;
	
	i = argc - 3;
	j = 1;
	data.pid_numb = 1;
	data.pipe = malloc(sizeof(int) * i);
	data.pidx = malloc(sizeof(pid_t)* i);
	data.pidx[0] = fork();
	if (data.pidx[0] == 0)
		first_child(data, argv, envp);
	while (j + 1 < i && i > 2)
	{
		//printf("j is equal to : %d, and pid_numb is : %d and i is : %d\n", j, data.pid_numb, i);
		data.pidx[data.pid_numb] = fork ();
		if (data.pidx[data.pid_numb] == 0)
			mid_child(data, j, argv, envp);
		j++;
		data.pid_numb++;
	}
	data.pidx[data.pid_numb] = fork();
	if (data.pidx[data.pid_numb] == 0)
		last_child(data, j, argv, envp);
}

void	first_child(t_pipe data, char **argv, char **envp)
{
	dup2(data.pipe[1], 1);
	close(data.pipe[0]);
	dup2(data.infile, 0);
	data.cmd_args = ft_split(argv[2], ' ');
	data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
	if (!data.cmd)
	{
		child_free(&data);
		msg(ERR_CMD);
		exit(1);
	}
	execve(data.cmd, data.cmd_args, envp);
}

void	last_child(t_pipe data, int j, char **argv, char **envp)
{
	dup2(data.pipe[2 * j - 2], 0);
	close(data.pipe[2 * j - 1]);
	dup2(data.outfile, 1);
	data.cmd_args = ft_split(argv[j + 2], ' ');
	data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
	if (!data.cmd)
	{
		child_free(&data);
		msg(ERR_CMD);
		exit(1);
	}
	execve(data.cmd, data.cmd_args, envp);
}
