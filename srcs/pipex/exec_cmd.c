/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:40:18 by welee             #+#    #+#             */
/*   Updated: 2024/09/11 08:01:04 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(t_pipex *pipex, char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		if (args)
			free_split(args);
		free_exit(pipex, EXIT_FAILURE);
	}
	cmd_path = find_cmd_path(args[0], envp);
	if (!cmd_path)
	{
		free_split(args);
		free_exit(pipex, EXIT_FAILURE);
	}
	if (execve(cmd_path, args, envp) == -1)
	{
		free(cmd_path);
		free_split(args);
		free_exit(pipex, EXIT_FAILURE);
	}
	free(cmd_path);
	free_split(args);
}
