/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:39:00 by welee             #+#    #+#             */
/*   Updated: 2024/09/13 17:39:29 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Handle the first command in the pipeline
 * @param pipex The pipex struct
 * @param pipefd The pipe file descriptors
 */
static void	handle_first_cmd(t_pipex *pipex, int *pipefd)
{
	int	fd_in;

	if (!pipex->here_doc)
	{
		fd_in = open(pipex->file1, O_RDONLY);
		if (fd_in < 0)
		{
			ft_putstr_fd("pipex: ", STDERR_FILENO);
			ft_putstr_fd(pipex->file1, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			free_exit(pipex, EXIT_FAILURE);
		}
		else
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
	}
	dup2(pipefd[1], STDOUT_FILENO);
}

/**
 * @brief Handle the last command in the pipeline
 * @param pipex The pipex struct
 * @param pipefd The pipe file descriptors
 */
static void	handle_last_cmd(t_pipex *pipex, int *pipefd)
{
	int	fd_out;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (pipex->here_doc)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd_out = open(pipex->file2, flags, 0644);
	if (fd_out < 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(pipex->file2, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		free_exit(pipex, EXIT_FAILURE);
	}
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

/**
 * @brief Handle the middle command in the pipeline
 * @param prev_pipe The previous pipe file descriptors
 * @param next_pipe The next pipe file descriptors
 */
static void	handle_middle_cmd(int *prev_pipe, int *next_pipe)
{
	dup2(prev_pipe[0], STDIN_FILENO);
	dup2(next_pipe[1], STDOUT_FILENO);
}

/**
 * @brief Wait for the child processes to finish
 * @param pipes The pipes
 */
static void	wait_pids(t_pipex *pipex, pid_t *pids, int num_cmds)
{
	int	status;
	int	i;
	int	last_status;

	i = 0;
	while (i < num_cmds)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			error_exit("waitpid", pipex, EXIT_FAILURE);
		if (i == num_cmds - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
			else
				last_status = EXIT_FAILURE;
		}
		i++;
	}
	free_exit(pipex, last_status);
}

/**
 * @brief Setup the pipes and execute the commands
 * @param pipex The pipex struct
 * @param envp The environment variables
 */
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
				handle_last_cmd(pipex, pipex->pipes[i - 1]);
			else
				handle_middle_cmd(pipex->pipes[i - 1], pipex->pipes[i]);
			close_pipes(pipex->pipes, pipex->num_cmds);
			execute_cmd(pipex, pipex->cmds[i], envp);
			free_exit(pipex, EXIT_FAILURE);
		}
		i++;
	}
	close_pipes(pipex->pipes, pipex->num_cmds);
	wait_pids(pipex, pipex->pids, pipex->num_cmds);
}
