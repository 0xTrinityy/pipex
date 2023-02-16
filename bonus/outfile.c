/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:55:32 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/16 19:55:33 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/pipex_bonus.h"


int    out_file(int argc, char **argv, t_pipe *data)
{
    int     a;

    if (data->doc == 1)
        a = open(argv[argc - 1], O_APPEND | O_CREAT | O_RDWR, 0000644);
    else
        a = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
    return (a);
}