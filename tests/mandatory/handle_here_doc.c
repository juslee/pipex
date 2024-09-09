/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:50:01 by welee             #+#    #+#             */
/*   Updated: 2024/09/06 15:15:50 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

void	handle_here_doc(char *limiter)
{
	char	*line;
	int		pipe_fd[2];
	int		lim_len;

	if (pipe(pipe_fd) == -1)
		handle_error("Pipe creation failed");
	lim_len = ft_strlen(limiter);
	while (1)
	{
		write(1, "heredoc> ", ft_strlen("heredoc> "));
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, lim_len) == 0 && line[lim_len] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}
