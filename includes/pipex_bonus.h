/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:53:23 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/16 11:36:22 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define ERR_INFILE "Infile error\n"
# define ERR_OUTFILE "Outfile error\n"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe error \n"
# define ERR_CMD "Command not found\n"
# define ERR_HEREDOC "Here_doc error\n"

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	pid_t	*pid;
	int     pidx;
	int     pid_numb;
	int     pipe_nb;
	int     cmd_nb;
	int     doc;
	int		*pipe;
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;

}			t_pipe;

char		*find_path(char **envp);
void		close_pipes(t_pipe *data);
int			msg(char *err);
void		msg_error(char *err);
void    close_all(t_pipe *data);
void	close_pipes(t_pipe *data);
void	parent_free(t_pipe *data);
void	child_free(t_pipe *data);
char	*get_cmd(char **paths, char *cmd);
void	first_child(t_pipe pipex, char **argv, char **envp);
void	last_child(t_pipe pipex, int j, char **argv, char **envp);
void    multiple_cmd(t_pipe data, char **argv, char **envp);
void     is_heredoc(char **argv, t_pipe *data);

int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *s);
int		find_nl(char *str);
char	*str_join(char *s1, char *s2);
char	*get_line(char *str);
char	*trim_rem(char *str);
int		some_error(char *str);


#endif