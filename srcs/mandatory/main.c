/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:06:38 by welee             #+#    #+#             */
/*   Updated: 2024/09/04 15:12:28 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	extern char	**environ;

	if (argc != 5)
	{
		write(STDERR_FILENO, "Usage: ./pipex file1 cmd1 cmd2 file2\n",
			ft_strlen("Usage: ./pipex file1 cmd1 cmd2 file2\n"));
		return (1);
	}
	pipex(argc, argv, environ);
	return (0);
}
