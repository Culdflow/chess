/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_pieces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:10:38 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/19 18:00:04 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/chess.h"

t_moves	*moves_fou(t_vector2 pos, int is_white, t_piece **sim_board)
{
	return (check_diag(pos, vec2(8, 8), vec2(8, 8), is_white, 1, sim_board));
}

t_moves	*moves_queen(t_vector2 pos, int is_white, t_piece **sim_board)
{
	t_moves	*move;
	t_moves	*file;
	t_moves	*line;

	move = check_diag(pos, vec2(8, 8), vec2(8, 8), is_white, 1, sim_board);
	file = check_file(pos, vec2(8, 8), is_white, 1, sim_board);
	line = check_line(pos, vec2(8, 8), is_white, 1, sim_board);
	move_add_move(&move, file);
	move_add_move(&move, line);
	return (move);
}

t_moves	*moves_rook(t_vector2 pos, int is_white, t_piece **sim_board)
{
	t_moves	*move;
	t_moves	*line;

	move = check_file(pos, vec2(8, 8), is_white, 1, sim_board);
	line = check_line(pos, vec2(8, 8), is_white, 1, sim_board);
	move_add_move(&move, line);
	return (move);
}

t_moves	*moves_king(t_vector2 pos, int is_white, t_piece **sim_board)
{
	t_moves	*move;
	t_moves	*file;
	t_moves	*line;

	move = check_diag(pos, vec2(1, 1), vec2(1, 1), is_white, 1, sim_board);
	file = check_file(pos, vec2(1, 1), is_white, 1, sim_board);
	line = check_line(pos, vec2(1, 1), is_white, 1, sim_board);
	move_add_move(&move, file);
	move_add_move(&move, line);
	return (move);
}

t_moves	*moves_pawn(t_vector2 pos, int is_white, t_piece **sim_board)
{
	t_moves	*file;
	t_moves	*eat;

	file = NULL;
	eat = NULL;
	if (is_white == 1)
	{
		if (pos.y == 6)
			file = check_file(pos, vec2(2, 0), is_white, 0, sim_board);
		else
			file = check_file(pos, vec2(1, 0), is_white, 0, sim_board);
	}
	else
	{
		if (pos.y == 1)
			file = check_file(pos, vec2(0, 2), is_white, 0, sim_board);
		else
			file = check_file(pos, vec2(0, 1), is_white, 0, sim_board);
	}
	eat = pawn_eat(pos, is_white, sim_board);
	move_add_move(&file, eat);
	return (file);
}

t_moves	*moves_horse(t_vector2 pos, int is_white)
{
	return (check_horse_moves(pos, is_white));
}

t_moves	*get_moves_pieces(t_vector2 pos, t_piece piece, t_piece **sim_board)
{
	int	is_white;

	is_white = 0;
	if (piece <= 1)
		return (NULL);
	if (piece < 8)
		is_white = 1;
	if (piece == PION_B || piece == PION_N)
		return (moves_pawn(pos, is_white, sim_board));
	if (piece == CHEV_B || piece == CHEV_N)
		return (moves_horse(pos, is_white));
	if (piece == TOUR_B || piece == TOUR_N)
		return (moves_rook(pos, is_white, sim_board));
	if (piece == FOU_B || piece == FOU_N)
		return (moves_fou(pos, is_white, sim_board));
	if (piece == REIN_B || piece == REIN_N)
		return (moves_queen(pos, is_white, sim_board));
	if (piece == ROI_B || piece == ROI_N)
		return (moves_king(pos, is_white, sim_board));
	return (NULL);
}