#include "../../include/cubed.h"

void draw_img(mlx_image_t *img, mlx_texture_t *texture)
{
    int dst_x;
    int dst_y;
	int y;
	int x;

	dst_y = 20;
	dst_x = (WIDTH - texture->width) / 2;
	y = 0;
    while (y < (int)texture->height)
	{
		x = 0;
        while (x < (int)texture->width)
		{
			my_put_pixel(img, dst_x + x, dst_y + y, get_texture_color(texture, x, y));
			x++;
        }
		y++;
    }
}

void	draw_info(t_data *data, char flag)
{
	if (flag == 'F')
		draw_img(data->cubed->info, data->texture->infoF);
	else if (flag == 'D')
		draw_img(data->cubed->info, data->texture->infoD);
	else if (flag == 'K')
		draw_img(data->cubed->info, data->texture->infoDC);
}