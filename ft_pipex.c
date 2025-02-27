/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:37:18 by astefane          #+#    #+#             */
/*   Updated: 2025/02/27 19:02:35 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	create_child(t_fd_pipex *pipex, char **argv,
char **envir, int is_parent)
{
	pid_t	child;

	child = fork();
	if (child == -1)
	{
		perror(ERR_FORK);
		exit(EXIT_FAILURE);
	}
	if (child == 0)
	{
		if (is_parent)
		{
			ft_parent_fd(argv, *pipex);
			ft_cmd(argv[3], envir);
		}
		else
		{
			ft_children_fd(argv, *pipex);
			ft_cmd(argv[2], envir);
		}
		exit(EXIT_FAILURE);
	}
}

int	wait_for_children(pid_t child1, pid_t child2)
{
	int	status1;
	int	status2;

	waitpid(child1, &status1, 0);
	waitpid(child2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (EXIT_FAILURE);
}

void	ft_children_fd(char **argv, t_fd_pipex pipex)
{
	int	in_fd;

	in_fd = open(argv[1], O_RDONLY, 0644);
	if (in_fd < 0)
	{
		perror(ERRO_INFILE);
		close(pipex.pipefd[0]);
		close(pipex.pipefd[1]);
		exit(EXIT_FAILURE);
	}
	close(pipex.pipefd[0]);
	if (dup2(in_fd, STDIN_FILENO) == -1
		|| dup2(pipex.pipefd[1], STDOUT_FILENO) == -1)
	{
		perror(ERRO_DUP);
		close(in_fd);
		close(pipex.pipefd[1]);
		exit(EXIT_FAILURE);
	}
	close(in_fd);
	close(pipex.pipefd[1]);
}

void	ft_parent_fd(char **argv, t_fd_pipex pipex)
{
	int	out_fd;

	out_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		perror(ERRO_OUFILE);
		close(pipex.pipefd[0]);
		close(pipex.pipefd[1]);
		exit(EXIT_FAILURE);
	}
	close(pipex.pipefd[1]);
	if (dup2(pipex.pipefd[0], STDIN_FILENO) == -1
		|| dup2(out_fd, STDOUT_FILENO) == -1)
	{
		perror(ERRO_DUP);
		close(out_fd);
		close(pipex.pipefd[0]);
		exit(EXIT_FAILURE);
	}
	close(out_fd);
	close(pipex.pipefd[0]);
}

int	main(int argc, char **argv, char **envir)
{
	t_fd_pipex	pipex;
	pid_t		child1;
	pid_t		child2;

	child1 = 0;
	child2 = 0;

	pipex = (t_fd_pipex){0};
	if (arg_isvalid(argc, argv) == 0 || pipe(pipex.pipefd) == -1)
	{
		perror(ERR_ARG);
		exit(EXIT_FAILURE);
	}
	create_child(&pipex, argv, envir, 0);
	create_child(&pipex, argv, envir, 1);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	return (wait_for_children(child1, child2));
}
