/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:41:50 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/03 17:35:02 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*void    free_child(t_pipe *data)
{

}

void    free_parent(t_pipe *data)
{

}*/
void    close_all(t_pipe *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
}