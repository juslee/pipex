/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:06:38 by welee             #+#    #+#             */
/*   Updated: 2024/07/15 17:10:36 by welee            ###   ########.fr       */
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
	pipex(argv, environ);
	return (0);
}
