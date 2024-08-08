/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:32:35 by dolifero          #+#    #+#             */
/*   Updated: 2024/05/29 18:40:30 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_realloc(char **str, size_t len, size_t new_len)
{
	char	*new_str;
	size_t	i;

	i = 0;
	new_str = malloc(new_len);
	if (!new_str)
	{
		ft_printf("Memory allocation failed\n");
		return (0);
	}
	while (i < len)
	{
		new_str[i] = (*str)[i];
		i++;
	}
	free(*str);
	*str = new_str;
	return (1);
}
