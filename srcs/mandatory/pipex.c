/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:57:35 by welee             #+#    #+#             */
/*   Updated: 2024/09/06 15:24:23 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	pipex(int argc, char **argv, char **envp)
// {
// 	t_pipex	px;
// 	pid_t	*pids;
// 	int		i;
// 	int		arg_index;

// 	px.here_doc = (ft_strcmp(argv[1], "here_doc") == 0);
// 	if (px.here_doc)
// 	{
// 		px.num_cmds = argc - 4;
// 		px.infile = NULL;
// 		arg_index = 3;
// 	}
// 	else
// 	{
// 		px.num_cmds = argc - 3;
// 		px.infile = argv[1];
// 		arg_index = 2;
// 	}
// 	px.outfile = argv[argc - 1];
// 	setup_pipes(&px, px.num_cmds);
// 	pids = malloc(sizeof(pid_t) * px.num_cmds);
// 	if (!pids)
// 		handle_error("Memory allocation failed");
// 	if (px.here_doc)
// 		handle_here_doc(argv[2]);
// 	i = 0;
// 	while (i < px.num_cmds)
// 	{
// 		pids[i] = fork_and_exec(&px, argv[i + arg_index], envp, i);
// 		i++;
// 	}
// 	close_pipes(&px, px.num_cmds);
// 	wait_for_children(pids, px.num_cmds);
// 	free(pids);
// 	free_pipes(&px, px.num_cmds);
// }

void	initialize_pipex(t_pipex *px, int argc, char **argv)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		px->here_doc = 1;
		px->num_cmds = argc - 4;
		px->infile = NULL;
		px->arg_index = 3;
	}
	else
	{
		px->here_doc = 0;
		px->num_cmds = argc - 3;
		px->infile = argv[1];
		px->arg_index = 2;
	}
	px->outfile = argv[argc - 1];
}

pid_t	*allocate_pids(int num_cmds)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pids)
		handle_error("Memory allocation failed");
	return (pids);
}

void	execute_commands(t_pipex *px, char **argv, char **envp, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < px->num_cmds)
	{
		pids[i] = fork_and_exec(px, argv[i + px->arg_index], envp, i);
		i++;
	}
}

void	cleanup(t_pipex *px, pid_t *pids)
{
	free(pids);
	free_pipes(px, px->num_cmds);
}

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	px;
	pid_t	*pids;

	initialize_pipex(&px, argc, argv);
	setup_pipes(&px, px.num_cmds);
	pids = allocate_pids(px.num_cmds);
	if (px.here_doc)
		handle_here_doc(argv[2]);
	execute_commands(&px, argv, envp, pids);
	close_pipes(&px, px.num_cmds);
	wait_for_children(pids, px.num_cmds);
	cleanup(&px, pids);
}
