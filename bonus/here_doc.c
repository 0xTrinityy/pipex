/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:32:18 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/16 19:49:49 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void    read_doc(char **argv, t_pipe *data)
{
	int     fd;
	char    *buffer;
	
	data->infile = open("here_doc", O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (data->infile < 0)
		msg_error(ERR_HEREDOC);
	while (1)
	{
		write(1, "here_doc input >\n", 17);
		buffer = get_next_line(fd);
		if (!buffer || !ft_strncmp(buffer, argv[2], ft_strlen(argv[2])))
		{
			printf("nothing to read anymore\n");
			break;
		}
		write(data->infile, buffer,ft_strlen(buffer));
		free(buffer);
		
	}
	close(data->infile);
	open(data->infile, O_RDONLY, 0000644);
	dup2(data->infile, 0);
}


void     is_heredoc(char **argv, t_pipe *data)
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
	printf("is there an here_doc : %d\n", data->doc);
}