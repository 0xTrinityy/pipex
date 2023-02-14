/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exe_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:53:41 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/14 16:48:07 by tbelleng         ###   ########.fr       */
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

/*void	mid_child(t_pipe data, int j, char **argv, char **envp)
{
	dup2(data.pipe[2 * j + 1], 1);
	//close(data.pipe[2 * j - 1]);
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
	data.pidx = malloc(sizeof(pid_t) * i);
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
	//printf("at the end pid numb is : %d\n", data.pid_numb);
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
*/
/*mid child 
	dup2(data.pipe[2 * (j + 1) + 1], 1);
	close(data.pipe[2 * j - 1]);
	dup2(data.pipe[2 * j], 0);
	
	last
	dup2(data.pipe[2 * j - 2], 0);
	close(data.pipe[2 * j - 1]);
	dup2(data.outfile, 1);

*/
void    to_dup(int infile, int outfile)
{
	dup2(infile, 0);
	dup2(outfile, 1);
}


void    multiple_cmd(t_pipe data, char **argv, char **envp)
{
	data.pid[data.pidx] = fork();
	if (!data.pid[data.pidx])
	{
		if (data.pidx == 0)
			to_dup(data.infile, data.pipe[1]);
		else if (data.pidx == data.cmd_nb - 1)
			to_dup(data.pipe[2 * data.pidx - 2], data.outfile);
		else
			to_dup(data.pipe[2 * data.pidx - 2], data.pipe[2 * data.pidx + 1]);
		close_pipes(&data);
		data.cmd_args = ft_split(argv[data.pidx + 2], ' ');
		data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
		if (!data.cmd)
		{
			child_free(&data);
			msg(ERR_CMD);
			exit(1);
		}
		execve(data.cmd, data.cmd_args, envp);
	}
}