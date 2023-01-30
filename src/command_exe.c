/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:18:19 by tbelleng          #+#    #+#             */
/*   Updated: 2023/01/30 16:41:47 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    command_exec(char **envp, int fd_in, int *file)
{
	char *options[2] = {"env", NULL};
	char **tab;
	char *tmp;
	char *cmd_path;
	int path;
	int new_file;
	int new_file1;
	int i;

	i = 0;
	new_file = dup2(fd_in, STDIN_FILENO);
	new_file1 = dup2(file[1], STDOUT_FILENO);
	close(fd_in);
	close(file[1]);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			break;
		i++;
	}
	tab = ft_split(envp[i], ':');
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

void    command_exec2(char **envp)
{
	char *options[2] = {"env", NULL};
	char **tab;
	char *tmp;
	char *cmd_path;
	int path;
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			break;
		i++;
	}
	tab = ft_split(envp[i], ':');
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