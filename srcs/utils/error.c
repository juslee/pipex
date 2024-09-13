/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:55:07 by welee             #+#    #+#             */
/*   Updated: 2024/09/13 17:33:26 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Print error message
 * @param err The error message
 * @param msg The message
 */
void	error_msg(char *err, char *msg)
{
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

/**
 * @brief Print the program name with the error message and exit
 * @param prog_name The program name
 * @param code The exit code
 */
void	error_args(char *prog_name, int code)
{
	ft_putstr_fd("Usage: ", STDERR_FILENO);
	ft_putstr_fd(prog_name, STDERR_FILENO);
	ft_putendl_fd(" file1 cmd1 cmd2 ... file2", STDERR_FILENO);
	exit(code);
}

/**
 * @brief Print the error message, free the pipex and exit
 * @param msg The error message
 * @param pipex The pipex struct
 * @param code The exit code
 */
void	error_exit(const char *msg, t_pipex *pipex, int code)
{
	perror(msg);
	free_pipex(pipex);
	exit(code);
}

/**
 * @brief Free the pipex and exit
 * @param pipex The pipex struct
 * @param code The exit code
 */
void	free_exit(t_pipex *pipex, int code)
{
	free_pipex(pipex);
	exit(code);
}
