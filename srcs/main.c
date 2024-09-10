/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:28 by welee             #+#    #+#             */
/*   Updated: 2024/09/10 22:18:39 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		error_args("Usage: ./pipex file1 cmd1 cmd2 ... file2\n", EXIT_FAILURE);
	parse_args(argc, argv, &pipex);
	create_pipes(&pipex);
	setup_pipes(&pipex, envp);
	free_pipex(&pipex);
	return (EXIT_SUCCESS);
}
