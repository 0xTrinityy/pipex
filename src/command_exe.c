/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:18:19 by tbelleng          #+#    #+#             */
/*   Updated: 2023/01/26 17:19:18 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    command_exec(char **envp)
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
        cmd_path = ft_strjoin(tab[i], "ps");
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