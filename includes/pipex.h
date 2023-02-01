/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:24:22 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/01 18:19:09 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct t_list
{
    pid_t   child;
    pid_t   child2;
    pid_t   res;
    pid_t   res2;
    int     status;
    int     status2;
    int     pipe[2];
    int     file_in;
    int     file_out;
    int     path;
    char    **envp;

}   t_pipe;

void    command_exec(t_pipe *data, int ac, char **av);
void    command_exec2(t_pipe *data, int ac, char **av);




#endif