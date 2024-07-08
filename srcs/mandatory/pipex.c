/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:57:35 by welee             #+#    #+#             */
/*   Updated: 2024/07/08 15:13:45 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid;

	if (argc != 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", STDERR_FILENO);
		return (1);
	}
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Error: Pipe failed\n", STDERR_FILENO);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error: Fork failed\n", STDERR_FILENO);
		return (1);
	}
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(argv[1], &argv[1], envp);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(argv[4], &argv[4], envp);
	}
	return (0);
}
