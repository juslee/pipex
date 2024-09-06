/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:05:26 by welee             #+#    #+#             */
/*   Updated: 2024/09/06 10:44:00 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_file(t_pipex *px, char *file, int flag)
{
	if (flag == O_RDONLY)
	{
		px->fd_in = open(file, flag);
		if (px->fd_in < 0)
			handle_error(file);
	}
	else
	{
		px->fd_out = open(file, flag, 0644);
		if (px->fd_out < 0)
			handle_error(file);
	}
}

// void	open_files(t_pipex *px, char **argv)
// {
// 	px->fd_in = open(argv[1], O_RDONLY);
// 	if (px->fd_in < 0)
// 		handle_error(argv[1]);
// 	px->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (px->fd_out < 0)
// 		handle_error(argv[4]);
// }
