/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:50:42 by welee             #+#    #+#             */
/*   Updated: 2024/09/13 17:31:51 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Free the split string
 * @param split The split string
 */
void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/**
 * @brief Close the pipes
 * @param pipes The pipes
 * @param num_cmds The number of commands
 */
void	close_pipes(int **pipes, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		if (pipes[i][0] != -1)
			close(pipes[i][0]);
		if (pipes[i][1] != -1)
			close(pipes[i][1]);
		i++;
	}
}

/**
 * @brief Free the pipes
 * @param pipes The pipes
 * @param num_cmds The number of commands
 */
void	free_pipes(int **pipes, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	if (pipes)
		free(pipes);
}

/**
 * @brief Free the commands
 * @param cmds The commands
 * @param num_cmds The number of commands
 */
void	free_cmds(char **cmds, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		if (cmds[i])
			free(cmds[i]);
		i++;
	}
	if (cmds)
		free(cmds);
}

/**
 * @brief Free the pipex structure
 * @param pipex The pipex structure
 */
void	free_pipex(t_pipex *pipex)
{
	if (pipex->cmds)
		free(pipex->cmds);
	if (pipex->pipes)
		free_pipes(pipex->pipes, pipex->num_cmds);
	if (pipex->pids)
		free(pipex->pids);
}
