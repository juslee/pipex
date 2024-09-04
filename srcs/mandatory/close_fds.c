/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:09:53 by welee             #+#    #+#             */
/*   Updated: 2024/09/04 15:59:52 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *px)
{
	if (px->pipe_fd[0] != -1)
	{
		close(px->pipe_fd[0]);
		px->pipe_fd[0] = -1;
	}
	if (px->pipe_fd[1] != -1)
	{
		close(px->pipe_fd[1]);
		px->pipe_fd[1] = -1;
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

void	close_fds(t_pipex *px)
{
	close_pipes(px);
	close_files(px);
}
