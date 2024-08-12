/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:21:57 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/12 02:11:23 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "./cubed.h"

//CHECKING
int		ft_isappr(char c);
int		check_args(int argc, char **argv);

//PARSING
t_input	*parse_file(char *filename);

//FREEING
void	free_params(t_input *input);
void	free_input(t_input *input);

//UTILS
void	remove_newline(char *line);

//DEBUG
void	print_input(t_input *input);

#endif
