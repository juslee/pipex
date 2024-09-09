/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:09:53 by welee             #+#    #+#             */
/*   Updated: 2024/09/06 11:14:52 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *px, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		if (px->pipes[i][0] != -1)
		{
			close(px->pipes[i][0]);
			px->pipes[i][0] = -1;
		}
		if (px->pipes[i][1] != -1)
		{
			close(px->pipes[i][1]);
			px->pipes[i][1] = -1;
		}
		i++;
	}
}

void	close_files(t_pipex *px)
{
	if (px->fd_in != -1)
	{
		close(px->fd_in);
		px->fd_in = -1;
	}
	if (px->fd_out != -1)
	{
		close(px->fd_out);
		px->fd_out = -1;
	}
}

void	close_fds(t_pipex *px, int num_cmds)
{
	close_pipes(px, num_cmds);
	close_files(px);
}
