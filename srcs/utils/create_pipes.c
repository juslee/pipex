/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:54:15 by welee             #+#    #+#             */
/*   Updated: 2024/09/13 17:34:50 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Create the pipes
 * @param pipex The pipex structure
 */
void	create_pipes(t_pipex *pipex)
{
	int	i;

	pipex->pipes = malloc((pipex->num_cmds - 1) * sizeof(int *));
	if (!pipex->pipes)
		error_exit("Error: malloc failed for pipes", pipex,
			EXIT_FAILURE);
	i = 0;
	while (i < pipex->num_cmds - 1)
	{
		pipex->pipes[i] = malloc(2 * sizeof(int));
		if (!pipex->pipes[i])
			error_exit("Error: malloc failed for pipe descriptors", pipex,
				EXIT_FAILURE);
		if (pipe(pipex->pipes[i]) == -1)
			error_exit("Error: pipe creation failed", pipex, EXIT_FAILURE);
		i++;
	}
}
