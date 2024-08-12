/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:22:58 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/12 01:57:11 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

int	main(int argc, char **argv)
{
	t_input	*input;

	if (!check_args(argc, argv))
		return (1);
	input = parse_file(argv[1]);
	if (!input)
		return (free_input(input), 1);
	print_input(input);
	free_input(input);
	return (0);
}
