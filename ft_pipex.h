/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:37:32 by astefane          #+#    #+#             */
/*   Updated: 2025/02/01 19:54:29 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "./libft/libft.h"

# define ERR_FLASH "Error"
# define ERR_ARG "Error Arg or Pipe"
# define ERR_FORK "Error Fork"
# define ERRO_INFILE "Error infile"
# define ERRO_DUP "Error DUP"
# define ERRO_OUFILE "Error outfile"

typedef struct s_fd_pipex
{
	int	pid;
	int	pipefd[2];
}	t_fd_pipex;

void	ft_cmd(char *argv, char **envir);
int		arg_isvalid(int argc, char **argv);
char	**cmd_managment(char *cmd);
char	*find_execpath(char **envir);
char	*create_path(char *possible_path, char *command);
void	free_and_exit(char **args, char **paths, int exit_code);
void	execute_command(char **args, char **paths, char **envir);

#endif