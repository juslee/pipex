/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:28 by welee             #+#    #+#             */
/*   Updated: 2024/09/13 14:30:57 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		error_args(argv[0], EXIT_FAILURE);
	parse_args(argc, argv, &pipex);
	create_pipes(&pipex);
	if (pipex.here_doc)
		handle_here_doc(&pipex, pipex.file1);
	setup_pipes(&pipex, envp);
}
