/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:16:00 by astefane          #+#    #+#             */
/*   Updated: 2025/01/20 18:06:46 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	**cmd_managment(char *cmd)
{
	char	**cmd_split;
	char	*cmd_only;
	char	*arg_only;

	cmd_split = ft_split(cmd, ' ');
	cmd_only = ft_strdup(cmd_split[0]);
	ft_freedoom(cmd_split);
	arg_only = (ft_strchr(cmd, 39));
	if (arg_only == NULL)
		arg_only = ft_strchr(cmd, 34);
	if (arg_only == NULL)
	{
		free(cmd_only);
		return (ft_split(cmd, ' '));
	}
	else
	{
		cmd_split = malloc(sizeof(char *) * 3);
		if (!cmd_split)
			return (NULL);
		cmd_split[0] = cmd_only;
		cmd_split[1] = ft_strtrim(arg_only, "'");
		cmd_split[2] = NULL;
		return (cmd_split);
	}
}

char	*find_execpath(char **envir)
{
	char	*path;
	int		i;

	i = 0;
	while (ft_strncmp(envir[i], "PATH", 4) != 0)
		i++;
	path = envir[i];
	return (path);
}

char	*create_path(char *possible_path, char *command)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(possible_path, "/");
	path = ft_strjoin(temp, command);
	return (path);
}
