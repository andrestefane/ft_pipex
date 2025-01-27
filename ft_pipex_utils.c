/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:06:04 by astefane          #+#    #+#             */
/*   Updated: 2025/01/27 18:48:31 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_cmd(char *argv, char **envir)
{
	char	**args;
	char	**possibble_path;
	char	*path_line;
	char	*path;
	int		i;

	args = cmd_managment(argv);
	path_line = find_execpath(envir);
	possibble_path = ft_split(path_line, ':');
	i = 0;
	while (possibble_path[i] != NULL)
	{
		path = create_path(possibble_path[i], args[0]);
		if (access(path, X_OK) != -1)
			execve(path, args, envir);
		free(path);
		i++;
	}
	perror(ERR_FLASH);
	perror(args[0]);
	ft_freedoom(args);
	ft_freedoom(possibble_path);
	exit (-1);
}
