/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:32:18 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/21 14:57:59 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void    read_doc(char **argv, t_pipe *data)
{
	int     fd;
	char    *buffer;
	
	fd = open(".here_doc", O_WRONLY | O_TRUNC | O_CREAT , 0000644);
	if (fd < 0)
		msg_error(ERR_HEREDOC);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buffer = get_next_line(0);
		if (!ft_strncmp(buffer, argv[2], ft_strlen(argv[2])))
			break;
		write(fd, buffer, ft_strlen(buffer));
		//write(fd, "\n", 1);
		free(buffer);
	}
	free(buffer);
	close(fd);
	data->infile = open(".here_doc", O_RDONLY);
	dup2(data->infile, 0);
	//unlink("here_doc");
}


void    is_heredoc(char **argv, t_pipe *data)
{
	int	a;

	a = 0;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		data->doc = 1;
		read_doc(argv, data);
	}
	else
	{
		data->doc = 0;
		data->infile = open(argv[1], O_RDONLY);
	}	
	//printf("is there an here_doc : %d\n", data->doc);
}