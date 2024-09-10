/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:51:32 by welee             #+#    #+#             */
/*   Updated: 2024/09/10 00:34:02 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_args(int argc, char **argv, t_pipex *pipex)
{
	if (argc != 5)
		error_args("Usage: ./pipex file1 cmd1 cmd2 file2\n", EXIT_FAILURE);
	pipex->file1 = argv[1];
	pipex->file2 = argv[argc - 1];
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
}
