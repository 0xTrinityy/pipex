/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:18:19 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/03 18:52:27 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char    **cmd_pathing(t_pipe *data)
{
	int     i;
	char    **tab;
	char    *tmp;
	
	
	i = 0;
	while (data->envp[i])
	{
		if (ft_strnstr(data->envp[i], "PATH", 4))
			break;
		i++;
	}
	tab = ft_split(data->envp[i], ':');
	i = 0;
	while (tab[i] != 0)
	{
		tmp = tab[i];
		tab[i] = ft_strjoin(tab[i], "/");
		free(tmp);
		i++;
	}
	return (tab);
}

void    command_exec(t_pipe *data, int ac, char **av)
{
	char *options[2] = {"env", NULL};
	char **tab;
	int i;

	dup2(data->pipe[1], STDOUT_FILENO);
	close(data->pipe[0]);
	dup2(data->file_in, STDERR_FILENO);
	tab = cmd_pathing(data);
	i = 0;
    while (tab[i])
    {
        data->cmd_path = ft_strjoin(tab[i], av[ac - 3]);
        if (access(data->cmd_path, F_OK | X_OK) == 0)
        {
            execv(data->cmd_path, options);
		} 
        i++;
    }
	//error_occur("Command doesnt exist");
    return ;
}

void    command_exec2(t_pipe *data, int ac, char **av)
{
	char *options[2] = {"env", NULL};
	char **tab;
	char *tmp;
	int		i;
	
	dup2(data->pipe[0], STDIN_FILENO);
	close(data->pipe[1]);
	dup2(data->file_out, STDOUT_FILENO);
	i = 0;
	//free(data->cmd_path);
	tab = cmd_pathing(data);
	while (tab[i])
    {
        data->cmd_path = ft_strjoin(tab[i], av[ac - 2]);
        if (access(data->cmd_path, F_OK | X_OK) == 0)
        {
            execv(data->cmd_path, options);
		} 
        i++;
    }
    return ;
}