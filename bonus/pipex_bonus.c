/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:53:56 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/14 18:47:20 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void    new_pipe(t_pipe *data, int argc)
{
	int     i;
	
	i = 0;
	data->cmd_nb = argc - 3;
	while (i < data->cmd_nb - 1)
	{
		if (pipe(data->pipe + (2 * i)) < 0)
			parent_free(data);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	data;
	int     i;

	if (argc < 6)
		return (msg(ERR_INPUT));
	i = 0;
	data.infile = open(argv[1], O_RDONLY);
	if (data.infile < 0)
		msg_error(ERR_INFILE);
	data.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (data.outfile < 0)
		msg_error(ERR_OUTFILE);
	if (pipe(data.pipe) < 0)
		msg_error(ERR_PIPE);
	data.pipe_nb = 2 * ((argc - 3) - 1);
	data.pipe = malloc(sizeof(int *) * data.pipe_nb);
	data.paths = find_path(envp);
	data.cmd_paths = ft_split(data.paths, ':');
	new_pipe(&data, argc);
	data.pidx = 0;
	printf("cmd commad equal to %d\n", data.cmd_nb);
	data.pid = malloc(sizeof(pid_t) * (data.cmd_nb - 1));
	while (data.pidx < data.cmd_nb)
	{
		multiple_cmd(data, argv, envp);
		printf("pidx equal to %d\n", data.pidx);
		data.pidx++;
	}
	close_pipes(&data);
	while (i < data.cmd_nb)
	{
		waitpid(data.pid[i], NULL, 0);
		printf("i equal to %d\n", i);
		i++;
	}
	parent_free(&data);
	return (0);
}