/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:25:49 by welee             #+#    #+#             */
/*   Updated: 2024/09/06 11:26:32 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipes(t_pipex *px, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		free(px->pipes[i]);
		i++;
	}
	free(px->pipes);
}
