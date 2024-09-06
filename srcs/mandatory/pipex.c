/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:57:35 by welee             #+#    #+#             */
/*   Updated: 2024/09/06 11:27:03 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	px;
	pid_t	*pids;
	int		i;

	px.infile = argv[1];
	px.outfile = argv[argc - 1];
	px.num_cmds = argc - 3;
	setup_pipes(&px, px.num_cmds);
	pids = malloc(sizeof(pid_t) * px.num_cmds);
	if (!pids)
		handle_error("Memory allocation failed");
	i = 0;
	while (i < px.num_cmds)
	{
		pids[i] = fork_and_exec(&px, argv[i + 2], envp, i);
		i++;
	}
	close_pipes(&px, px.num_cmds);
	wait_for_children(pids, px.num_cmds);
	free(pids);
	free_pipes(&px, px.num_cmds);
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
