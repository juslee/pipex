/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:26:19 by welee             #+#    #+#             */
/*   Updated: 2024/09/06 15:18:13 by welee            ###   ########.fr       */
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
	int		**pipes;
	int		num_cmds;
	int		fd_in;
	int		fd_out;
	char	*infile;
	char	*outfile;
	int		here_doc;
	int		arg_index;
}		t_pipex;

void	pipex(int argc, char **argv, char **envp);
// void	execute_cmd(char *cmd, char **envp);
void	handle_error(char *msg);
void	handle_error_command_not_found(char *cmd);
void	handle_error_is_a_directory(char *cmd);
void	handle_here_doc(char *limiter);
void	setup_pipes(t_pipex *px, int num_cmds);
// void	open_files(t_pipex *px, char **argv);
void	open_file(t_pipex *px, char *file, int flag);
pid_t	fork_and_exec(t_pipex *px, char *cmd, char **envp, int i);
void	close_pipes(t_pipex *px, int num_cmds);
void	close_files(t_pipex *px);
void	close_fds(t_pipex *px, int num_cmds);
//void	wait_for_children(pid_t pid1, pid_t pid2);
void	wait_for_children(pid_t px[], int pid_count);
char	*find_cmd_path(char *cmd, char **envp);
char	*join_path(const char *dir, const char *cmd);
char	**get_paths_from_env(char **envp);
char	*check_absolute_or_relative_cmd(char *cmd);
void	free_split(char **split);
void	free_pipes(t_pipex *px, int num_cmds);
#endif
