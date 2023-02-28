/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:53:49 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/28 19:59:50 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	msg_error(char *err)
{
	perror(err);
	exit (1);
}

void	close_pipes(t_pipe *data)
{
	int	i;

	i = 0;
	//fprintf(stderr, "%d\n", data->pipe_nb);
	while (i < (data->pipe_nb))
	{
		close(data->pipe[i]);
		//fprintf(stderr, "i vaut %d\n", i);
		i++;
	}
	//fprintf(stderr, "fd vaut %d\n", data->pipe[3]);
}

void    close_all(t_pipe *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
	//close(data->pipe[2]);
	close(data->outfile);
	close(data->infile);
	free(data->pipe);
}

void	parent_free(t_pipe *data, int argc)
{
	int	i;

	i = 0;
	close(data->infile);
	close(data->outfile);
	if (data->doc == 1 && unlink(".here_doc") == -1)
		msg_error(ERR_UNLINK);
	while (data->cmd_paths[i])
	{
		free(data->cmd_paths[i]);
		i++;
	}
	free(data->cmd_paths);
	free(data->pipe);
	free(data->pid);
	close(argc - 1);
	close(6);
	close(5);
}

void	child_free(t_pipe *data)
{
	int	i;

	i = 0;
	while (data->cmd_args[i])
	{
		free(data->cmd_args[i]);
		i++;
	}
	free(data->cmd_args);
	free(data->cmd);
}
