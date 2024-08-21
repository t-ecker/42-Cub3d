/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:45:02 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/20 19:01:16 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	pad_strings(char **arr)
{
	int	max_length;
	int	i;
	int	len;

	if (arr == NULL)
		return ;
	max_length = 0;
	i = -1;
	while (arr[++i])
	{
		len = ft_strlen(arr[i]);
		if (len > max_length)
			max_length = len;
	}
	i = -1;
	while (arr[++i])
	{
		len = ft_strlen(arr[i]);
		if (len < max_length)
		{
			arr[i] = ft_realloc(arr[i], len, max_length + 1);
			ft_memset(arr[i] + len, ' ', max_length - len);
			arr[i][max_length] = '\0';
		}
	}
	arr[i] = NULL;
}
