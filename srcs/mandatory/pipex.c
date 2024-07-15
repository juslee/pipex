/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:57:35 by welee             #+#    #+#             */
/*   Updated: 2024/07/15 17:11:38 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char **argv, char **envp)
{
	t_pipex	px;

	setup_pipes(&px);
	open_files(&px, argv);
	fork_and_exec(&px, argv[2], 1, envp);
	fork_and_exec(&px, argv[3], 0, envp);
	close_fds(&px);
	wait_for_children();
}