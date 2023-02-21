/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:53:23 by tbelleng          #+#    #+#             */
/*   Updated: 2023/02/21 13:32:15 by tbelleng         ###   ########.fr       */
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
# define ERR_UNLINK "Unlink error\n"

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
void	parent_free(t_pipe *data, int agrc);
void	child_free(t_pipe *data);
char	*get_cmd(char **paths, char *cmd);
void    multiple_cmd(t_pipe data, char **argv, char **envp);
void    is_heredoc(char **argv, t_pipe *data);
int    out_file(int argc, char **argv, t_pipe *data);

char	*ft_get_line(char *save);
char	*ft_save(char *save);
char	*ft_read_and_save(int fd, char *save);
char	*get_next_line(int fd);
size_t	ft_strlen1(char *str);
char	*ft_strchr1(char *s, int c);
char	*ft_strjoin1(char *s1, char *s2);






#endif