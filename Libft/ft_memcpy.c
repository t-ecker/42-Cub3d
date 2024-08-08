/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:56 by dolifero          #+#    #+#             */
/*   Updated: 2024/03/08 18:26:30 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*source;
	int			i;

	dest = (char *)dst;
	source = (const char *)src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (n--)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	source[] = "Hello, world!";
// 	char	destination[20];

// 	printf("Source: %s\n", source);
// 	printf("Destination before: %s\n", destination);
// 	ft_memcpy(destination, source, 8);
// 	printf("Copied string: %s\n", destination);
// 	return (0);
// }
