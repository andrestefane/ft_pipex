/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:06:04 by astefane          #+#    #+#             */
/*   Updated: 2025/03/08 18:38:38 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include "libft/libft.h"

//Possible_path divide el PATH usando ; como delimitador.
//Esto se hace para buscador ejecutables en directorios especificos.


void	ft_cmd(char *argv, char **envir)
{
	char	**args;
	char	**possible_paths;
	char	*path_line;

	if (!envir || !*envir)
		return ;
	args = cmd_managment(argv);
	if (!args || !*args)
		exit_with_error(ERR_FLASH, 127);
	path_line = find_execpath(envir);
	if (!path_line)
	{
		ft_freedoom(args);
		exit_with_error(ERR_FLASH, 1);
	}
	possible_paths = ft_split(path_line, ':');
	if (!possible_paths)
	{
		ft_freedoom(args);
		exit_with_error(ERR_FLASH, 1);
	}
	execute_command(args, possible_paths, envir);
}

//Separa con comillas el primer comando(cmd_split), lo duplica(cmd_split[0] y lo guarda en cmd_only),
//busca si el argumento(cmd) tiene comillas simple o dobles y si las tiene las guarda(en arg_only).
//Si no las tiene devolvemos el cmd entre comillas y si viene entre comillas,
//Hacemos una nueva array manualmente, se reserva un array de punteros,se le asigna en cmd_split[0] = el primer argumento(cmd_only)
//y le decimos que con ft_strtrim eliminemos las comillas y que la array finaliza con null.

char	**cmd_managment(char *cmd)
{
	char	**cmd_split;
	char	*cmd_only;
	char	*arg_only;

	if (!cmd || !*cmd)
		exit_with_error(ERR_FLASH, 127);
	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split || !cmd_split[0])
	{
		ft_freedoom(cmd_split);
		return (NULL);
	}
	cmd_only = ft_strdup(cmd_split[0]);
	ft_freedoom(cmd_split);
	arg_only = ft_strchr(cmd, 39);
	if (!arg_only)
	{
		free(cmd_only);
		return (split_command(cmd));
	}
	cmd_split = malloc(sizeof(char *) * 3);
	if (!cmd_split)
		exit_with_error(ERR_FLASH, 1);
	cmd_split = (char *[]){cmd_only, ft_strtrim(arg_only, "'"), NULL};
	return (cmd_split);
}

//*path se usa para almacenar el puntero a la variable de entorno PATH
//En el while compara los primeros 4 caracteres de envir con PATH y
//sigue hasta encontrar PATH
//Si no encuentra PATH salimos del programa

char	*find_execpath(char **envir)
{
	int	i;

	i = 0;
	if (!envir)
		return (NULL);
	while (envir[i])
	{
		if (ft_strncmp(envir[i], "PATH=", 5) == 0)
			return (envir[i] + 5);
		i++;
	}
	return (NULL);
}

//Se encarga de buscar y ejecutar un comando de las rutas de PATH
//En el while buscamos el comando por los directorios de PATH
//En PATH construye una ruta completa
//Verifica con access si la ruta existe y ejecutable
//Execve remplaza el proceso actual por el nuevo comando
//Si no se ejecuta liberamos y damos error

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
			free_and_exit(args, paths, 0);
		if (access(path, X_OK) != -1)
			execve(path, args, envir);
		free(path);
		i++;
	}
	perror(ERR_FLASH);
	perror(args[0]);
	free_and_exit(args, paths, 127);
}

//Construye una ruta completa a un comando combinando un directorio de PATH con el nombre del comando
//Concadenamos el directorio con '/'
//concadenamos el resultado con el comando


char	*create_path(char *possible_path, char *command)
{
	char	*path;
	char	*temp;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	temp = ft_strjoin(possible_path, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, command);
	free(temp);
	return (path);
}
