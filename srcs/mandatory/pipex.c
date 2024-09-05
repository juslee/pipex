/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:57:35 by welee             #+#    #+#             */
/*   Updated: 2024/09/05 22:08:59 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	px;
	pid_t	pid[2];

	setup_pipes(&px);
	px.infile = argv[1];
	px.outfile = argv[argc - 1];
	px.is_first = 1;
	px.is_last = 0;
	pid[0] = fork_and_exec(&px, argv[2], envp);
	px.is_first = 0;
	px.is_last = 1;
	pid[1] = fork_and_exec(&px, argv[3], envp);
	close_fds(&px);
	// wait_for_children(pid, 2);
}

// void	pipex(int argc, char **argv, char **envp)
// {
// 	t_pipex	px;
// 	int		i;
// 	pid_t	pid;

// 	px.pid_count = 0;
// 	i = 2;
// 	while (i < argc - 2)
// 	{
// 		setup_pipes(&px);
// 		px.is_first = (i == 2);
// 		px.is_last = 0;
// 		pid = fork_and_exec(&px, argv[i], envp);
// 		px.pids[px.pid_count++] = pid;
// 		close_pipes(&px);
// 		i++;
// 	}
// 	px.is_last = 1;
// 	px.is_first = 0;
// 	pid = fork_and_exec(&px, argv[argc - 2], envp);
// 	px.pids[px.pid_count++] = pid;
// 	wait_for_children(&px);
// 	close_files(&px);
// }
