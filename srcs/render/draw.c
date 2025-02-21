/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:16:16 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/21 14:53:44 by dfeve            ###   ########.fr       */
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

	if (!data)
		return ;
	clamp_vec2(&start, vec2(0, 0), vec2(800, 800));
	clamp_vec2(&end, vec2(0, 0), vec2(800, 800));
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

void	draw_rectangle_no_fill(t_img *data, t_vector2 start, t_vector2 end, int color)
{
	int	i;

	i = start.x;
	while (i <= end.x)
	{
		my_mlx_pixel_put(data, i, start.y, color);
		my_mlx_pixel_put(data, i++ , end.y, color);
	}
	i = start.y;
	while (i <= end.y)
	{
		my_mlx_pixel_put(data, start.x, i, color);
		my_mlx_pixel_put(data, end.x , i++, color);
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

void	draw_board(t_mlx *mlx, int	color1, int color2)
{
	t_vector2	cursor;

	cursor = vec2(0, 0);
	while (cursor.y < 8)
	{
		cursor.x = 0;
		while (cursor.x < 8)
		{
			if ((cursor.x + cursor.y) % 2 == 0)
				draw_rectangle(&mlx->imgs[0], mul_vec2(cursor, vec2(100, 100)), mul_vec2(add_vec2(cursor, vec2(1, 1)), vec2(100, 100)), color1);
			else
				draw_rectangle(&mlx->imgs[0], mul_vec2(cursor, vec2(100, 100)), mul_vec2(add_vec2(cursor, vec2(1, 1)), vec2(100, 100)), color2);
			cursor.x++;
		}
		cursor.y++;
	}
}

void	draw_piece(t_mlx *mlx, t_piece piece, t_vector2 pos)
{
	if (piece == PION_B)
		xpm_file_to_img(mlx, "sprites/white_pawn.xpm", pos);
	else if (piece == PION_N)
		xpm_file_to_img(mlx, "sprites/black_pawn.xpm", pos);
	else if (piece == TOUR_B)
		xpm_file_to_img(mlx, "sprites/white_rook.xpm", pos);
	else if (piece == TOUR_N)
		xpm_file_to_img(mlx, "sprites/black_rook.xpm", pos);
	else if (piece == CHEV_B)
		xpm_file_to_img(mlx, "sprites/white_horse.xpm", pos);
	else if (piece == CHEV_N)
		xpm_file_to_img(mlx, "sprites/black_horse.xpm", pos);
	else if (piece == FOU_B)
		xpm_file_to_img(mlx, "sprites/white_fou.xpm", pos);
	else if (piece == FOU_N)
		xpm_file_to_img(mlx, "sprites/black_fou.xpm", pos);
	else if (piece == REIN_B)
		xpm_file_to_img(mlx, "sprites/white_queen.xpm", pos);
	else if (piece == REIN_N)
		xpm_file_to_img(mlx, "sprites/black_queen.xpm", pos);
	else if (piece == ROI_B)
		xpm_file_to_img(mlx, "sprites/white_king.xpm", pos);
	else if (piece == ROI_N)
		xpm_file_to_img(mlx, "sprites/black_king.xpm", pos);
}
