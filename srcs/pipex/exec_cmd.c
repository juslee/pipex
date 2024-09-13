/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:40:18 by welee             #+#    #+#             */
/*   Updated: 2024/09/13 16:49:20 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Read and modify error message
 * @param fd File descriptor
 */
static void	read_and_modify_error(int fd)
{
	char	buffer[1024];
	ssize_t	n;
	char	*modified_error;

	n = read(fd, buffer, sizeof(buffer) - 1);
	if (n > 0)
	{
		buffer[n] = '\0';
		modified_error = ft_strreplace(buffer, "/bin/sh", "pipex");
		if (modified_error)
		{
			write(STDERR_FILENO, modified_error, ft_strlen(modified_error));
			free(modified_error);
		}
		else
			write(STDERR_FILENO, buffer, n);
	}
}

/**
 * @brief Wait for child process to finish
 * @param pipex The pipex structure
 * @param pid Process ID
 */
static void	wait_child_process(t_pipex *pipex, pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		free_exit(pipex, EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		free_exit(pipex, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		free_exit(pipex, 128 + WTERMSIG(status));
	else
		free_exit(pipex, EXIT_FAILURE);
}

/**
 * @brief Child process
 * @param pipex The pipex structure
 * @param pipefd Pipe file descriptor
 * @param cmd Command
 * @param envp Environment variables
 */
static void	child_process(t_pipex *pipex, int *pipefd, char *cmd, char **envp)
{
	char	*args[4];

	close(pipefd[0]);
	if (dup2(pipefd[1], STDERR_FILENO) == -1)
		error_exit("dup2", pipex, EXIT_FAILURE);
	close(pipefd[1]);
	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = cmd;
	args[3] = NULL;
	execve(args[0], args, envp);
	error_exit("pipex", pipex, 127);
}

/**
 * @brief Parent process
 * @param pipex The pipex structure
 * @param pipefd Pipe file descriptor
 * @param pid Process ID
 */
static void	parent_process(t_pipex *pipex, int *pipefd, pid_t pid)
{
	close(pipefd[1]);
	read_and_modify_error(pipefd[0]);
	close(pipefd[0]);
	wait_child_process(pipex, pid);
}

/**
 * @brief Execute command
 * @param pipex The pipex structure
 * @param cmd Command
 * @param envp Environment variables
 */
void	execute_cmd(t_pipex *pipex, char *cmd, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		error_exit("pipe", pipex, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		error_exit("fork", pipex, EXIT_FAILURE);
	if (pid == 0)
		child_process(pipex, pipefd, cmd, envp);
	else
		parent_process(pipex, pipefd, pid);
}

//// Second try
// void	execute_cmd(t_pipex *pipex, char *cmd, char **envp)
// {
// 	char	*args[4];

// 	args[0] = "/bin/sh";
// 	args[1] = "-c";
// 	args[2] = cmd;
// 	args[3] = NULL;
// 	if (execve(args[0], args, envp) == -1)
// 	{
// 		perror("pipex");
// 		free_exit(pipex, EXIT_FAILURE);
// 	}
// }

//// First try
// void	execute_cmd(t_pipex *pipex, char *cmd, char **envp)
// {
// 	char	**args;
// 	char	*cmd_path;

// 	args = parse_cmd(cmd);
// 	for (int i = 0; args[i]; i++)
// 	{
// 		write(2, "args[i]: ", 9);
// 		write(2, args[i], ft_strlen(args[i]));
// 		write(2, "\n", 1);
// 	}
// 	if (!args || !args[0])
// 	{
// 		free_split(args);
// 		free_exit(pipex, EXIT_FAILURE);
// 	}
// 	cmd_path = find_cmd_path(args[0], envp);
// 	if (!cmd_path)
// 	{
// 		free_split(args);
// 		free_exit(pipex, EXIT_FAILURE);
// 	}
// 	if (execve(cmd_path, args, envp) == -1)
// 	{
// 		perror(args[0]);
// 		free(cmd_path);
// 		free_split(args);
// 		free_exit(pipex, EXIT_FAILURE);
// 	}
// }
