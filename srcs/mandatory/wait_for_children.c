/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:09:18 by welee             #+#    #+#             */
/*   Updated: 2024/07/15 17:32:29 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_children(pid_t pid1, pid_t pid2)
{
	int	status;

	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
