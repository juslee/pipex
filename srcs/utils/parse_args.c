/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:51:32 by welee             #+#    #+#             */
/*   Updated: 2024/09/10 15:54:30 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_args(int argc, char **argv, t_pipex *pipex)
{
	int	i;

	pipex->file1 = argv[1];
	pipex->file2 = argv[argc - 1];
	pipex->num_cmds = argc - 3;
	pipex->cmds = malloc(pipex->num_cmds * sizeof(char *));
	if (!pipex->cmds)
		error_exit("Error: malloc failed for commands", pipex, EXIT_FAILURE);
	pipex->pids = malloc(pipex->num_cmds * sizeof(pid_t));
	if (!pipex->pids)
		error_exit("Error: malloc failed for PIDs", pipex, EXIT_FAILURE);
	i = 0;
	while (i < pipex->num_cmds)
	{
		pipex->cmds[i] = argv[i + 2];
		i++;
	}
}
