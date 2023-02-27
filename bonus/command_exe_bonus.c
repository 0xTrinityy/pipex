/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exe_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:53:41 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/27 14:10:13 by tbelleng         ###   ########.fr       */
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

void    to_dup(int infile, int outfile)
{
	dup2(infile, 0);
	dup2(outfile, 1);
}

void    multiple_cmd(t_pipe data, char **argv, char **envp)
{
	//printf("%d\n", data.pidx);
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
		data.cmd_args = ft_split(argv[data.pidx + 2 + data.doc], ' ');
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