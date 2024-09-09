/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:15:29 by welee             #+#    #+#             */
/*   Updated: 2024/09/05 20:38:23 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*join_path(const char *dir, const char *cmd)
{
	char	*path;
	size_t	len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	path = (char *)malloc(len * sizeof(char));
	if (!path)
		return (NULL);
	ft_strlcpy(path, dir, len);
	ft_strlcat(path, "/", len);
	ft_strlcat(path, cmd, len);
	return (path);
}

char	**get_paths_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*find_cmd_in_paths(char **paths, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = join_path(paths[i], cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free_split(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	return (NULL);
}

int	ends_with_slash(const char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (len > 0 && cmd[len - 1] == '/')
		return (1);
	return (0);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	path_with_slash[1024];
	char	**paths;
	char	*cmd_path;

	if (ends_with_slash(cmd))
		handle_error_is_a_directory(cmd);
	if (ft_strchr(cmd, '/'))
		return (check_absolute_or_relative_cmd(cmd));
	ft_strlcpy(path_with_slash, cmd, sizeof(path_with_slash));
	ft_strlcat(path_with_slash, "/", sizeof(path_with_slash));
	if (access(path_with_slash, F_OK) == 0)
		handle_error_command_not_found(cmd);
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	paths = get_paths_from_env(envp);
	if (!paths)
		handle_error(cmd);
	cmd_path = find_cmd_in_paths(paths, cmd);
	if (!cmd_path)
	{
		free_split(paths);
		handle_error_command_not_found(cmd);
	}
	return (cmd_path);
}
