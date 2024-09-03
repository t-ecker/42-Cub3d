/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:32:35 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 13:59:48 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (!ptr)
		return (new_ptr);
	if (old_size > new_size)
		copy_size = new_size;
	else
		copy_size = old_size;
	if (copy_size > 0)
		ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}
