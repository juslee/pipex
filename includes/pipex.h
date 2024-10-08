/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:09:18 by welee             #+#    #+#             */
/*   Updated: 2024/09/13 17:43:11 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_pipex
{
	char	*file1;
	char	*file2;
	char	**cmds;
	int		num_cmds;
	int		**pipes;
	pid_t	*pids;
	int		here_doc;
}	t_pipex;

// Utils
void	parse_args(int argc, char **argv, t_pipex *pipex);

// Error handling
void	error_msg(char *err, char *msg);
void	error_args(char *msg, int code);
void	error_exit(const char *msg, t_pipex *pipex, int code);
void	free_exit(t_pipex *pipex, int code);

// Free
void	free_split(char **split);
void	free_pipes(int **pipes, int num_cmds);
void	free_pipex(t_pipex *pipex);
void	close_pipes(int **pipes, int num_cmds);

// Pipes
void	create_pipes(t_pipex *pipex);
void	setup_pipes(t_pipex *pipex, char **envp);
void	execute_cmd(t_pipex *pipex, char *cmd, char **envp);

// Parse Commands (NOT IN USE)
char	**parse_cmd(const char *cmd);

// Command path (NOT IN USE)
char	*find_cmd_path(char *cmd, char **envp);
char	*search_in_path_dirs(char *cmd, char **path_dirs);
char	*handle_direct_path(char *cmd);
char	*get_path_from_envp(char **envp);
char	*join_path(const char *dir, const char *cmd);

// Here_doc
void	handle_here_doc(t_pipex *pipex, char *limiter);

#endif
