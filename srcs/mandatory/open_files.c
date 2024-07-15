/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:05:26 by welee             #+#    #+#             */
/*   Updated: 2024/07/15 17:06:07 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipex *px, char **argv)
{
	px->fd_in = open(argv[1], O_RDONLY);
	if (px->fd_in < 0)
		handle_error("open error for input file");
	px->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->fd_out < 0)
		handle_error("open error for output file");
}
