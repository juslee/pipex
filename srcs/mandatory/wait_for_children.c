/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:09:18 by welee             #+#    #+#             */
/*   Updated: 2024/09/05 21:17:26 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	wait_for_children(pid_t pid1, pid_t pid2)
// {
// 	int	status;

// 	waitpid(pid1, &status, 0);
// 	waitpid(pid2, &status, 0);
// }

void	wait_for_children(pid_t pid[], int pid_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < pid_count)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
}

// void	wait_for_children(t_pipex *px)
// {
// 	int	i;
// 	int	status;

// 	i = 0;
// 	while (i < px->pid_count)
// 	{
// 		waitpid(px->pids[i], &status, 0);
// 		// if (WIFEXITED(status))
// 		// {
// 		// 	ft_printf("Process %d exited with status %d\n",
// 		// 		px->pids[i], WEXITSTATUS(status));
// 		// }
// 		// else if (WIFSIGNALED(status))
// 		// {
// 		// 	ft_printf("Process %d was killed by signal %d\n",
// 		// 		px->pids[i], WTERMSIG(status));
// 		// }
// 		i++;
// 	}
// }
