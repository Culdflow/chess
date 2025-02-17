/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:15:19 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/17 02:17:14 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/chess.h"

t_piece board[9][9] = {
	{TOUR_N, CHEV_N, FOU_N, REIN_N, ROI_N, FOU_N, CHEV_N, TOUR_N},
	{PION_N, PION_N, PION_N, PION_N, PION_N, PION_N, PION_N, PION_N,},
	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{PION_B, PION_B, PION_B, PION_B, PION_B, PION_B, PION_B, PION_B,},
	{TOUR_B, CHEV_B, FOU_B, REIN_B, ROI_B, FOU_B, CHEV_B, TOUR_B}
};

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

void	draw_pieces(t_mlx *mlx)
{
	t_vector2	cursor;

	cursor = vec2(0, 0);
	while (cursor.y < 8)
	{
		cursor.x = 0;
		while (cursor.x < 8)
		{
			draw_piece(mlx, board[cursor.y][cursor.x], mul_vec2(cursor, vec2(100, 100)));
			cursor.x++;
		}
		cursor.y++;
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