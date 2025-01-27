/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:37:18 by astefane          #+#    #+#             */
/*   Updated: 2025/01/27 20:56:09 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_children_fd(char **argv, t_fd_pipex pipex)
{
	int	in_fd;

	in_fd = open(argv[1], O_RDONLY, 0644);
	if (in_fd < 0)
		perror(ERRO_INFILE);
	close(pipex.pipefd[0]);
	if (dup2(in_fd, STDIN_FILENO) == -1
		|| dup2(pipex.pipefd[1], STDOUT_FILENO) == -1)
		perror(ERRO_DUP);
	close(in_fd);
	close(pipex.pipefd[1]);
}

void	ft_parent_fd(char **argv, t_fd_pipex pipex)
{
	int	out_fd;

	out_fd = open(argv[4], O_CREAT | O_WRONLY, 0644);
	if (out_fd < 0)
		perror (ERRO_OUFILE);
	close(pipex.pipefd[1]);
	if (dup2(pipex.pipefd[0], STDIN_FILENO) == -1
		|| dup2(out_fd, STDOUT_FILENO) == -1)
		perror(ERRO_DUP);
	close(out_fd);
	close(pipex.pipefd[0]);
}

int	main(int argc, char **argv, char **envir)
{
	t_fd_pipex	pipex;

	pipex = (t_fd_pipex){0};
	if (arg_isvalid(argc, argv) == 0 || pipe(pipex.pipefd) == -1)
	{
		perror (ERR_ARG);
		exit(-1);
	}
	pipex.pid = fork();
	if (pipex.pid == -1)
	{
		perror(ERR_FORK);
		exit (-1);
	}
	if (pipex.pid == 0)
	{
		ft_children_fd(argv, pipex);
		ft_cmd(argv[2], envir);
	}
	wait(NULL);
	ft_parent_fd(argv, pipex);
	ft_cmd(argv[3], envir);
	return (0);
}
