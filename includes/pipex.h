/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:26:19 by welee             #+#    #+#             */
/*   Updated: 2024/07/15 16:59:01 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

typedef struct s_pipex
{
	int	fd_in;
	int	fd_out;
	int	pipe_fd[2];
}		t_pipex;

void	pipex(char **argv, char **envp);
void	execute_cmd(char *cmd, char **envp);
void	handle_error(char *msg);
void	setup_pipes(t_pipex *px);
void	open_files(t_pipex *px, char **argv);
void	fork_and_exec(t_pipex *px, char *cmd, int is_first, char **envp);
void	close_fds(t_pipex *px);
void	wait_for_children(void);
char	*find_cmd_path(char *cmd, char **envp);
char	*join_path(const char *dir, const char *cmd);
char	**get_paths_from_env(char **envp);
void	free_split(char **split);
#endif
