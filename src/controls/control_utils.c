/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:25:16 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/28 18:23:03 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	detect(char c)
{
	return (c == '1' || c == 'D' || c == 'F');
}

void collision(t_data *data, double newX, double newY)
{
    float buffer;
    int canmoveX;
    int canmoveY;
	
	canmoveY= 1;
	canmoveX= 1;
	buffer = 0.3;
    if (data->Map[(int)newY][(int)newX] == 'M')
	{
        clear_image(data->cubed->hand);
        draw_overlay_part(data->cubed->victory, data->texture->death, 0, 0);
    }
    if (detect(data->Map[(int)(data->posY + buffer)][(int)(newX + buffer)]) ||
        detect(data->Map[(int)(data->posY - buffer)][(int)(newX + buffer)]) ||
        detect(data->Map[(int)(data->posY + buffer)][(int)(newX - buffer)]) ||
        detect(data->Map[(int)(data->posY - buffer)][(int)(newX - buffer)]) ||
        detect(data->Map[(int)data->posY][(int)(newX + buffer)]) ||
        detect(data->Map[(int)data->posY][(int)(newX - buffer)]))
        canmoveX = 0;
    if (detect(data->Map[(int)(newY + buffer)][(int)(data->posX + buffer)]) ||
        detect(data->Map[(int)(newY + buffer)][(int)(data->posX - buffer)]) ||
        detect(data->Map[(int)(newY - buffer)][(int)(data->posX + buffer)]) ||
        detect(data->Map[(int)(newY - buffer)][(int)(data->posX - buffer)]) ||
        detect(data->Map[(int)(newY + buffer)][(int)data->posX]) ||
        detect(data->Map[(int)(newY - buffer)][(int)data->posX]))
        canmoveY = 0;
    if (canmoveX && canmoveY)
	{
        data->posX = newX;
        data->posY = newY;
    }
	else if (canmoveX)
        data->posX = newX;
    else if (canmoveY)
        data->posY = newY;
}
