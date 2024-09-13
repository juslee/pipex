/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 00:02:32 by welee             #+#    #+#             */
/*   Updated: 2024/09/13 17:34:38 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** NOT IN USE **/

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

char	*get_path_from_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*handle_direct_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else
	{
		perror(cmd);
		return (NULL);
	}
}

char	*search_in_path_dirs(char *cmd, char **path_dirs)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		full_path = join_path(path_dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**path_dirs;
	char	*result;

	if (ft_strchr(cmd, '/') != NULL)
		return (handle_direct_path(cmd));
	path_env = get_path_from_envp(envp);
	if (!path_env)
	{
		perror(cmd);
		return (NULL);
	}
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
	{
		perror(cmd);
		return (NULL);
	}
	result = search_in_path_dirs(cmd, path_dirs);
	free_split(path_dirs);
	if (result)
		return (result);
	error_msg(cmd, "command not found");
	return (NULL);
}
