/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:18:19 by tbelleng          #+#    #+#             */
/*   Updated: 2023/01/31 22:20:48 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    command_exec(t_pipe *data)
{
	char *options[2] = {"env", NULL};
	char **tab;
	char *tmp;
	char *cmd_path;
	int i;
	int new_file;
	int	new_file1;


	i = 0;
	new_file = dup2(data->file_in, STDIN_FILENO);
	new_file1 = dup2(data->pipe[1], STDOUT_FILENO);
	close(data->file_in);
	close(data->pipe[1]);
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
	i = 0;
	while (tab[i])
    {
        cmd_path = ft_strjoin(tab[i], "cat");
        if (access(cmd_path, F_OK | X_OK) == 0)
        {
            printf("%s\n", cmd_path);
            execv(cmd_path, options);
		}
        free(cmd_path); 
        i++;
    }
}

void    command_exec2(t_pipe *data)
{
	char *options[2] = {"env", NULL};
	char **tab;
	char *tmp;
	char *cmd_path;
	int		i;

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
	i = 0;
	while (tab[i])
    {
        cmd_path = ft_strjoin(tab[i], "pwd");
        if (access(cmd_path, F_OK | X_OK) == 0)
        {
            printf("%s\n", cmd_path);
            execv(cmd_path, options);
		}
        free(cmd_path); 
        i++;
    }
}