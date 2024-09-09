/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:06:28 by welee             #+#    #+#             */
/*   Updated: 2024/09/06 11:09:39 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	setup_pipes(t_pipex *px)
// {
// 	if (pipe(px->pipe_fd) == -1)
// 		handle_error("pipe error");
// }

void	setup_pipes(t_pipex *px, int num_cmds)
{
	int	i;

	px->pipes = malloc(sizeof(int *) * (num_cmds - 1));
	if (!px->pipes)
		handle_error("Pipe allocation failed");
	i = 0;
	while (i < num_cmds - 1)
	{
		px->pipes[i] = malloc(sizeof(int) * 2);
		if (!px->pipes[i])
			handle_error("Pipe allocation failed");
		if (pipe(px->pipes[i]) == -1)
			handle_error("Pipe creation failed");
		i++;
	}
}
