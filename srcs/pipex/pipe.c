/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:39:00 by welee             #+#    #+#             */
/*   Updated: 2024/09/11 00:26:04 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_first_cmd(t_pipex *pipex, int *pipefd)
{
	int	fd_in;

	fd_in = open(pipex->file1, O_RDONLY);
	if (fd_in < 0)
	{
		perror(pipex->file1);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(fd_in);
}

static void	handle_second_cmd(t_pipex *pipex, int *pipefd)
{
	int	fd_out;

	fd_out = open(pipex->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror(pipex->file2);
		exit(EXIT_FAILURE);
	}
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(pipefd[1]);
}

static void	handle_cmd(int *prev_pipe, int *next_pipe)
{
	dup2(prev_pipe[0], STDIN_FILENO);
	dup2(next_pipe[1], STDOUT_FILENO);
	close(prev_pipe[1]);
	close(next_pipe[0]);
}

static void	wait_pids(pid_t *pids, int num_cmds)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	setup_pipes(t_pipex *pipex, char **envp)
{
	int		i;

	i = 0;
	while (i < pipex->num_cmds)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] < 0)
			error_exit("Error forking for cmd", pipex, EXIT_FAILURE);
		if (pipex->pids[i] == 0)
		{
			if (i == 0)
				handle_first_cmd(pipex, pipex->pipes[i]);
			else if (i == pipex->num_cmds - 1)
				handle_second_cmd(pipex, pipex->pipes[i - 1]);
			else
				handle_cmd(pipex->pipes[i - 1], pipex->pipes[i]);
			execute_cmd(pipex->cmds[i], envp);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	close_pipes(pipex->pipes, pipex->num_cmds);
	wait_pids(pipex->pids, pipex->num_cmds);
}
