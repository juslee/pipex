/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:10:35 by welee             #+#    #+#             */
/*   Updated: 2024/09/13 14:17:11 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	update_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
}

static char	**append_arg(char **args, char *arg)
{
	int		i;
	char	**new_args;

	i = 0;
	while (args && args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (args && args[i])
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i++] = arg;
	new_args[i] = NULL;
	free(args);
	return (new_args);
}

char	**parse_cmd(const char *cmd)
{
	int		i;
	int		start;
	int		in_single;
	int		in_double;
	char	**args;

	i = 0;
	in_single = 0;
	in_double = 0;
	args = NULL;
	while (cmd[i])
	{
		while (cmd[i] == ' ')
			i++;
		start = i;
		while (cmd[i] && (cmd[i] != ' ' || in_single || in_double))
		{
			update_quotes(cmd[i], &in_single, &in_double);
			if (cmd[i] == '\\')
				i++;
			i++;
		}
		args = append_arg(args, ft_substr(cmd, start, i - start));
	}
	return (args);
}
