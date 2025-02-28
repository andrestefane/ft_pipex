/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:53:49 by astefane          #+#    #+#             */
/*   Updated: 2025/02/28 19:45:01 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	arg_isvalid(int argc, char **argv)
{
	int	i;
	int	value;

	i = 0;
	value = 1;
	while (argv[i])
	{
		if (!argv[i] || !ft_strcmp(argv[i], ""))
		{
			value = 0;
			break ;
		}
		i++;
	}
	if (argc != 5)
		value = 0;
	return (value);
}
