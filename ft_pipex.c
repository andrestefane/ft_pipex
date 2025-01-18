/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:37:18 by astefane          #+#    #+#             */
/*   Updated: 2025/01/18 20:00:31 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_children_fd(char **argv, t_fd_pipex pipex)
{
	int	in_fd;

	in_fd = open(argv[1], O_RDONLY, 0644);
	if (in_fd < 0)
		perror(ERR_FLASH);
	close(pipex.pipefd[0]);
	if (dup2(in_fd, STDIN_FILENO) == -1
		|| dup2(pipex.pipefd[1], STDOUT_FILENO) == -1)
		perror("Error\n In children for Dup2");
	close(in_fd);
	close(pipex.pipefd[1]);
}

int	main(int argc, char **argv, char **envir)
{
	t_fd_pipex	pipex;

	pipex = (t_fd_pipex){0};
	if (arg_isvalid(argc, argv) == 0 || pipe(pipex.pipefd) == -1)
	{
		write(2, "Error\nInvalid Arguments or Pipe error\n", 39);
		exit(-1);
	}
	pipex.pid = fork();
	if (pipex.pid == -1)
	{
		perror("Error fork");
		exit (-1);
	}
	if (pipex.pid == 0)
	{
		ft_children_fd(argv, pipex);
		ft_cmd(argv[2], envir);
	}
}
