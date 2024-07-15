/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:40:44 by welee             #+#    #+#             */
/*   Updated: 2024/07/15 17:17:25 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		perror("ft_split error");
		exit(EXIT_FAILURE);
	}
	cmd_path = find_cmd_path(args[0], envp);
	if (!cmd_path)
	{
		perror("Command not found");
		free_split(args);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_path, args, envp) == -1)
	{
		perror("execve error");
		free(cmd_path);
		free_split(args);
		exit(EXIT_FAILURE);
	}
	free(cmd_path);
	free_split(args);
}
