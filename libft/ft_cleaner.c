/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:08:16 by astefane          #+#    #+#             */
/*   Updated: 2025/01/20 17:12:55 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cleaner(char *str, char r)
{
	char	*temp;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str);
	if (!str || !*str)
		return (NULL);
	temp = (char *)malloc(len + 1);
	if (!temp)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != r)
			temp[j++] = str[i];
		i++;
	}
	temp[j] = '\0';
	free(str);
	return (temp);
}
