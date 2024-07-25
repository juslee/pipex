/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:57:35 by welee             #+#    #+#             */
/*   Updated: 2024/07/23 09:31:18 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char **argv, char **envp)
{
	t_pipex	px;
	pid_t	pid1, pid2;

	setup_pipes(&px);
	open_files(&px, argv);
	pid1 = fork_and_exec(&px, argv[2], 1, envp);
	if (pid1 == -1)
		handle_error("fork error");
	pid2 = fork_and_exec(&px, argv[3], 0, envp);
	if (pid2 == -1)
		handle_error("fork error");
	close_fds(&px);
	wait_for_children(pid1, pid2);
}
