/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:07:17 by welee             #+#    #+#             */
/*   Updated: 2024/07/16 15:26:20 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	fork_and_exec(t_pipex *px, char *cmd, int is_first, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (is_first)
		{
			dup2(px->fd_in, STDIN_FILENO);
			dup2(px->pipe_fd[1], STDOUT_FILENO);
			close(px->pipe_fd[0]);
		}
		else
		{
			dup2(px->pipe_fd[0], STDIN_FILENO);
			dup2(px->fd_out, STDOUT_FILENO);
			close(px->pipe_fd[1]);
		}
		execute_cmd(cmd, envp);
	}
	return (pid);
}
