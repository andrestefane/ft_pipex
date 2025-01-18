/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:06:04 by astefane          #+#    #+#             */
/*   Updated: 2025/01/18 20:28:03 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_cmd(char *argv, char **envir)
{
	char	**args;
	char	*path;

	if (!argv || !*argv)
		exit(-1);
	args = ft_split(argv, ' ');
	if (!args || !*args)
	{
		ft_freedoom(args);
		exit (-1);
	}
	
}
