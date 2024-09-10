/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:40:18 by welee             #+#    #+#             */
/*   Updated: 2024/09/10 12:28:51 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	cmd_path = find_cmd_path(args[0], envp);
	if (!cmd_path)
	{
		free_split(args);
		return ;
	}
	if (execve(cmd_path, args, envp) == -1)
	{
		free(cmd_path);
		free_split(args);
		error_exit(args[0], EXIT_FAILURE);
	}
	error_msg(cmd_path, "execve");
	free(cmd_path);
	free_split(args);
}
