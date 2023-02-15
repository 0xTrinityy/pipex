/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:32:18 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/15 18:12:24 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void    read_doc(char argv, t_pipe *data)
{
	int     fd;
	char    *buffer;
	
	fd = open("here_doc", O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (fd < 0)
		msg_error(ERR_HEREDOC);
	while (1)
	{
		write(1, "here_doc input >\n", 17);
		get_next_line(fd);
		
	}

}


void     is_heredoc(char **argv, t_pipe *data)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		data->doc = 1;
		read_doc(argv, data);
	}
	else
		data->doc = 0;
	printf("is there an here_doc : %d\n", data->doc);
}