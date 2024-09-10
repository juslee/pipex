/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:39:00 by welee             #+#    #+#             */
/*   Updated: 2024/09/10 12:21:43 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_first_cmd(t_pipex *pipex, int *pipefd, char **envp)
{
	int	fd_in;

	fd_in = open(pipex->file1, O_RDONLY);
	if (fd_in < 0)
		error_exit(pipex->file1, EXIT_FAILURE);
	dup2(fd_in, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(fd_in);
	execute_cmd(pipex->cmd1, envp);
}

static void	handle_second_cmd(t_pipex *pipex, int *pipefd, char **envp)
{
	int	fd_out;

	fd_out = open(pipex->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		error_exit(pipex->file2, EXIT_FAILURE);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(pipefd[1]);
	execute_cmd(pipex->cmd2, envp);
}

void	setup_pipes(t_pipex *pipex, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		error_exit("Error creating pipe", EXIT_FAILURE);
	pid1 = fork();
	if (pid1 < 0)
		error_exit("Error forking for cmd1", EXIT_FAILURE);
	if (pid1 == 0)
		handle_first_cmd(pipex, pipefd, envp);
	pid2 = fork();
	if (pid2 < 0)
		error_exit("Error forking for cmd2", EXIT_FAILURE);
	if (pid2 == 0)
		handle_second_cmd(pipex, pipefd, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
