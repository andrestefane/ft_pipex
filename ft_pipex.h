/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:37:32 by astefane          #+#    #+#             */
/*   Updated: 2025/01/18 20:09:46 by astefane         ###   ########.fr       */
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


typedef struct s_fd_pipex
{
	int	pid;
	int	pipefd[2];
}	t_fd_pipex;

void	ft_cmd(char *argv, char **envir);
int		arg_isvalid(int argc, char **argv);

#endif