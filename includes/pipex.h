/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:09:18 by welee             #+#    #+#             */
/*   Updated: 2024/09/10 11:15:51 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_pipex
{
	char	*file1;
	char	*file2;
	char	*cmd1;
	char	*cmd2;
}	t_pipex;

typedef struct s_cmd
{
	char	*cmd;
	char	**envp;
	int		is_first;
	int		is_last;
}	t_cmd;

// Utils
void	parse_args(int argc, char **argv, t_pipex *fds);

// Error handling
void	error_msg(char *err, char *msg);
void	error_args(char *msg, int code);
void	error_exit(const char *msg, /*pid_t *pids, t_fds *fds,*/ int code);

// Free
void	free_split(char **split);

// Execution
void	setup_pipes(t_pipex *pipex, char **envp);
void	execute_cmd(char *cmd, char **envp);

// Command path
char	*find_cmd_path(char *cmd, char **envp);
char	*get_path_from_envp(char **envp);
char	*join_path(const char *dir, const char *cmd);


#endif
