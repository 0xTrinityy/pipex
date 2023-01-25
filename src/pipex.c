/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:24:13 by tbelleng          #+#    #+#             */
/*   Updated: 2023/01/25 15:41:17 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*char    *path_find(char *str)
{
	char *path;
	int i;
	
	path = ft_strnstr(str, "PATH", 4);
	
	if (path == "PATH")
		

}*/

int     main(int ac, char **av, char **envp)
{
	char *options[2] = {"env", NULL};
	char **tab;
	char *tmp;
	char *cmd_path;
	int path;
	int i;

	i = 0;
	(void)ac;
	(void)av;
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
        cmd_path = ft_strjoin(tab[i], "ls");
        if (access(cmd_path, F_OK | X_OK) == 0)
        {
            printf("%s\n", cmd_path);
            execv(cmd_path, options);
		}
        free(cmd_path); 
        i++;
    }
    printf("FIN\n");
	return (0);
}