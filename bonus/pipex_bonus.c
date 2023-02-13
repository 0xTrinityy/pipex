/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:53:56 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/13 15:09:30 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
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
	data.paths = find_path(envp);
	data.cmd_paths = ft_split(data.paths, ':');
	multiple_cmd(data, argc, argv, envp);
	close_all(&data);
	while (i < data.pid_numb)
	{
		waitpid(data.pidx[i], NULL, 0);
		i++;
	}
	parent_free(&data);
	return (0);
}