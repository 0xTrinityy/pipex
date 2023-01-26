/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:24:13 by tbelleng          #+#    #+#             */
/*   Updated: 2023/01/26 17:20:39 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*char    *path_find(char *str)
{
	char *path;
	int i;
	
	path = ft_strnstr(str, "PATH", 4);
	
	if (path == "PATH")
		

}*/

int     main(int ac, char **av, char **envp)
{
	pid_t child;
	pid_t res;
	int status;
	int file[2];
	(void)ac;
	(void)av;
	
	printf("forking...\n");
	printf("fork done !\n");
	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		command_exec(envp);
	}
	else if (child > 0)
	{
		res = waitpid(child, &status, 0);
		if (WIFEXITED(status))
		{
            printf("Process completed\n");
            command_exec2(envp);
		}
        else
            printf("interrupted...");
	}
	return (0);
}