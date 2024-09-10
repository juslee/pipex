/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:55:07 by welee             #+#    #+#             */
/*   Updated: 2024/09/10 11:16:56 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(char *err, char *msg)
{
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	error_args(char *msg, int code)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(code);
}

void	error_exit(const char *msg, /* pid_t *pids, t_fds *fds,*/ int code)
{
	perror(msg);
	// cleanup(pids, fds);
	exit(code);
}
