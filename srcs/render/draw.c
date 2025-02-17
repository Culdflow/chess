/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:16:16 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/17 02:25:54 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/chess.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	if (color != 0xe29c9c)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_rectangle(t_img *data, t_vector2 start, t_vector2 end, int color)
{
	t_vector2	cursor;
	t_vector2	goal;
	int			x;

	cursor = vec2_make_start(start, end);
	x = cursor.x;
	goal = vec2_make_end(start, end);
	while (cursor.y <= goal.y)
	{
		cursor.x = x;
		while (cursor.x <= goal.x)
		{
			my_mlx_pixel_put(data, cursor.x, cursor.y, color);
			cursor.x++;
		}
		cursor.y++;
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_length) + (x * img.bits_per_pixel / 8))));
}

void	put_img_to_img(t_img *dst, t_img src, int x, int y)
{
	int i;
	int j;

	i = 0;
	while(i < src.size.y) {
		j = 0;
		while (j < src.size.x) {
			my_mlx_pixel_put(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}
