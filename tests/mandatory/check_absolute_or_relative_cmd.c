/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_absolute_or_relative_cmd.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:37:10 by welee             #+#    #+#             */
/*   Updated: 2024/09/05 20:37:48 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_absolute_or_relative_cmd(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (cmd);
	handle_error(cmd);
	return (NULL);
}
