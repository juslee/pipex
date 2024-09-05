/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:07:17 by welee             #+#    #+#             */
/*   Updated: 2024/09/05 22:05:16 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_input(t_pipex *px, int is_first)
{
	if (is_first)
	{
		px->fd_in = open(px->infile, O_RDONLY);
		if (px->fd_in == -1)
			handle_error(px->infile);
		dup2(px->fd_in, STDIN_FILENO);
	}
	else
		dup2(px->pipe_fd[0], STDIN_FILENO);
}

void	handle_output(t_pipex *px, int is_last)
{
	if (is_last)
	{
		px->fd_out = open(px->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (px->fd_out == -1)
			handle_error(px->outfile);
		dup2(px->fd_out, STDOUT_FILENO);
	}
	else
		dup2(px->pipe_fd[1], STDOUT_FILENO);
}

pid_t	fork_and_exec(t_pipex *px, char *cmd, char **envp)
{
	pid_t	pid;
	char	*cmd_path;
	char	**cmd_args;

	pid = fork();
	if (pid == -1)
		handle_error("fork");
	if (pid == 0)
	{
		handle_input(px, px->is_first);
		handle_output(px, px->is_last);
		close_pipes(px);
		cmd_args = ft_split(cmd, ' ');
		cmd_path = find_cmd_path(cmd_args[0], envp);
		if (execve(cmd_path, cmd_args, envp) == -1)
		{
			free_split(cmd_args);
			handle_error(cmd);
		}
	}
	return (pid);
}
