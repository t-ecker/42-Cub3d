/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:14:12 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/07 13:15:15 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concatenated;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	concatenated = malloc(s1_len + s2_len + 1);
	if (!concatenated)
		return (NULL);
	ft_strlcpy(concatenated, s1, s1_len + 1);
	ft_strlcat(concatenated, s2, s1_len + s2_len + 1);
	return (concatenated);
}
