/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:06:04 by astefane          #+#    #+#             */
/*   Updated: 2025/02/01 20:24:59 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_cmd(char *argv, char **envir)
{
	char	**args;
	char	**possible_paths;
	char	*path_line;

	if (!envir || !*envir)
		return ;
	args = cmd_managment(argv);
	if (!args)
		exit(1);
	path_line = find_execpath(envir);
	if (!path_line)
	{
		ft_freedoom(args);
		exit(1);
	}
	possible_paths = ft_split(path_line, ':');
	if (!possible_paths)
	{
		ft_freedoom(args);
		exit(1);
	}
	execute_command(args, possible_paths, envir);
}

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
	if (!envir[i])
		return (NULL);
	return (path);
}

void	execute_command(char **args, char **paths, char **envir)
{
	char	*path;
	int		i;

	if (!envir || !*envir)
		return ;
	i = 0;
	while (paths[i] != NULL)
	{
		path = create_path(paths[i], args[0]);
		if (!path)
			free_and_exit(args, paths, 1);
		if (access(path, X_OK) != -1)
			execve(path, args, envir);
		free(path);
		i++;
	}
	perror(ERR_FLASH);
	perror(args[0]);
	free_and_exit(args, paths, 127);
}

char	*create_path(char *possible_path, char *command)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(possible_path, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, command);
	free(temp);
	return (path);
}
