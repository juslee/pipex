/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:09:53 by welee             #+#    #+#             */
/*   Updated: 2024/07/15 17:10:16 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_pipex *px)
{
	close(px->fd_in);
	close(px->fd_out);
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
}
