/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:07:17 by welee             #+#    #+#             */
/*   Updated: 2024/07/15 17:08:28 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_and_exec(t_pipex *px, char *cmd, int is_first, char **envp)
{
	if (fork() == 0)
	{
		if (is_first)
		{
			dup2(px->fd_in, STDIN_FILENO);
			dup2(px->pipe_fd[1], STDOUT_FILENO);
		}
		else
		{
			dup2(px->pipe_fd[0], STDIN_FILENO);
			dup2(px->fd_out, STDOUT_FILENO);
		}
		close(px->pipe_fd[0]);
		execute_cmd(cmd, envp);
	}
}
