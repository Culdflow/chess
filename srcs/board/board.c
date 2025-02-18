/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:15:19 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/18 06:31:12 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/chess.h"

// {TOUR_N, CHEV_N, FOU_N, REIN_N, ROI_N, FOU_N, CHEV_N, TOUR_N},
// 	{PION_N, PION_N, PION_N, PION_N, PION_N, PION_N, PION_N, PION_N,},
// 	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
// 	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
// 	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
// 	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
// 	{PION_B, PION_B, PION_B, PION_B, PION_B, PION_B, PION_B, PION_B,},
// 	{TOUR_B, CHEV_B, FOU_B, REIN_B, ROI_B, FOU_B, CHEV_B, TOUR_B}

t_piece board[9][9] = {
	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{ROI_N, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{RIEN, PION_N, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{RIEN, PION_B, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{RIEN, RIEN, CHEV_B, RIEN, RIEN, ROI_B, RIEN, RIEN},
	{TOUR_B, RIEN, TOUR_B, RIEN, RIEN, RIEN, RIEN, RIEN},
	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN}
};

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

int	is_piece_my_color(t_vector2 pos, int is_white)
{
	t_piece	piece;

	piece = board[pos.y][pos.x];
	if (((is_white == 1 && piece >= 8) || (is_white == 0 && piece < 8)) || piece == RIEN)
		return (-1);
	return (1);
}

t_moves	*check_file(t_vector2 pos, t_vector2 move_strength, int is_white, int take)
{
	t_moves		*result;
	t_vector2	cursor;
	t_vector2	check_pos;

	result = NULL;
	cursor = vec2(0, 1);
	check_pos = add_vec2(cursor, pos);
	if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) >= 0)
	{
		while (cursor.y <= move_strength.y && (board[check_pos.y] && board[check_pos.y][check_pos.x]))
		{
			if (board[check_pos.y][check_pos.x] == RIEN || take == 1)
				moves_add(&result, check_pos, is_white);
			if (board[check_pos.y][check_pos.x] != RIEN)
				break ;
			cursor.y++;
			check_pos = add_vec2(cursor, pos);
			if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) < 0)
				break ;
		}
	}
	cursor = vec2(0, 1);
	check_pos = sub_vec2(pos, cursor);
	if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) < 0)
		return (result);
	while (cursor.y <= move_strength.x && (board[check_pos.y] && board[check_pos.y][check_pos.x]))
	{
		if (board[check_pos.y][check_pos.x] == RIEN || take == 1)
			moves_add(&result, check_pos, is_white);
		if (board[check_pos.y][check_pos.x] != RIEN)
			break ;
		cursor.y++;
		check_pos = sub_vec2(pos, cursor);
		if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) < 0)
			return (result);
	}
	return (result);
}

t_moves	*check_line(t_vector2 pos, t_vector2 move_strength, int is_white, int take)
{
	t_moves		*result;
	t_vector2	cursor;
	t_vector2	check_pos;

	result = NULL;
	cursor = vec2(1, 0);
	check_pos = add_vec2(cursor, pos);
	if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) >= 0)
	{
		while (cursor.x <= move_strength.y && (board[check_pos.y] && board[check_pos.y][check_pos.x]))
		{
			if (board[check_pos.y][check_pos.x] == RIEN || take == 1)
				moves_add(&result, check_pos, is_white);
			if (board[check_pos.y][check_pos.x] != RIEN)
				break ;
			cursor.x++;
			check_pos = add_vec2(cursor, pos);
			if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) < 0)
				break ;
		}
	}
	cursor = vec2(1, 0);
	check_pos = sub_vec2(pos, cursor);
	if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) < 0)
		return (result);
	while (cursor.x <= move_strength.x && (board[check_pos.y] && board[check_pos.y][check_pos.x]))
	{
		if (board[check_pos.y][check_pos.x] == RIEN || take == 1)
			moves_add(&result, check_pos, is_white);
		if (board[check_pos.y][check_pos.x] != RIEN)
			break ;
		cursor.x++;
		check_pos = sub_vec2(pos, cursor);
		if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) < 0)
			return (result);
	}
	return (result);
}

t_moves	*do_diag(t_vector2 pos, t_vector2 move_strength_up, t_vector2 move_strength_down, int is_white, int take, int front, int inv)//ma fonction prefere jsp comment elle marche mais mashallah
{
	t_moves		*result;
	t_vector2	cursor;
	t_vector2	check_pos;

	result = NULL;
	cursor = vec2(1, 1);
	if (front == 1)
	{
		if (inv == 0)
			check_pos = add_vec2(cursor, pos);
		else
			check_pos = add_vec2(pos, vec2_inv_x(cursor));
		if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) < 0)
				return (result);
		while (cursor.y <= move_strength_up.y && (board[check_pos.y] && board[check_pos.y][check_pos.x]))
		{
			if (inv == 0)
			{
				check_pos = add_vec2(cursor, pos);
				if (board[check_pos.y][check_pos.x] == RIEN || take == 1)
					moves_add(&result, check_pos, is_white);
				if (board[check_pos.y][check_pos.x] != RIEN )
					break ;
			}
			else
			{
				check_pos = add_vec2(pos, vec2_inv_x(cursor));
				if (board[check_pos.y][check_pos.x] == RIEN || take == 1)
					moves_add(&result, check_pos, is_white);
				if (board[check_pos.y][check_pos.x] != RIEN)
					break ;
			}
			cursor.x++;
			cursor.y++;
			if (inv == 0)
				check_pos = add_vec2(cursor, pos);
			else
				check_pos = add_vec2(pos, vec2_inv_x(cursor));
			if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) < 0)
				return (result);
		}
	}
	else
	{
		if (inv == 0)
			check_pos = sub_vec2(pos, vec2_inv_x(cursor));
		else
			check_pos =  sub_vec2(pos, cursor);
		if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) < 0)
				return (result);
		while (cursor.y <= move_strength_down.y && (board[check_pos.y] && board[check_pos.y][check_pos.x]))
		{
			if (inv == 0)
			{
				if (board[check_pos.y][check_pos.x] == RIEN || take == 1)
					moves_add(&result, check_pos, is_white);
				if (board[check_pos.y][check_pos.x] != RIEN)
					break ;
			}
			else
			{
				if (board[check_pos.y][check_pos.x] == RIEN || take == 1)
					moves_add(&result, check_pos, is_white);
				if (board[check_pos.y][check_pos.x] != RIEN)
					break ;
			}
			cursor.x++;
			cursor.y++;
			if (inv == 0)
				check_pos = sub_vec2(pos, vec2_inv_x(cursor));
			else
				check_pos =  sub_vec2(pos, cursor);
			if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) < 0)
				return (result);
		}
	}
	return (result);
}

t_moves	*pawn_eat(t_vector2 pos, int is_white)
{
	t_moves		*result;
	t_vector2	test_pos;

	result = NULL;
	if (is_white == 1)
	{
		test_pos = sub_vec2(pos, vec2(1, 1));
		if (clamp_vec2(&test_pos, vec2(0, 0), vec2(7, 7)) > -1)
		{
			if (board[test_pos.y][test_pos.x] >= 8)
				moves_add(&result, test_pos, is_white);
		}
		test_pos = sub_vec2(pos, vec2(-1, 1));
		if (clamp_vec2(&test_pos, vec2(0, 0), vec2(7, 7)) > -1)
		{
			if (board[test_pos.y][test_pos.x] >= 8)
				moves_add(&result, test_pos, is_white);
		}
	}
	else
	{
		test_pos = add_vec2(pos, vec2(1, 1));
		if (clamp_vec2(&test_pos, vec2(0, 0), vec2(7, 7)) > -1)
		{
			if (board[test_pos.y][test_pos.x] > 1 && board[test_pos.y][test_pos.x] < 8)
				moves_add(&result, test_pos, is_white);
		}
		test_pos = add_vec2(pos, vec2(-1, 1));
		if (clamp_vec2(&test_pos, vec2(0, 0), vec2(7, 7)) > -1)
		{
			if (board[test_pos.y][test_pos.x] > 1 && board[test_pos.y][test_pos.x] < 8)
				moves_add(&result, test_pos, is_white);
		}
	}
	return (result);
}

t_moves	*check_horse_moves(t_vector2 pos, int is_white)
{
	t_moves	*result;

	result = NULL;
	moves_add(&result, add_vec2(pos, vec2(2, 1)), is_white);
	moves_add(&result, add_vec2(pos, vec2(-2, 1)), is_white);
	moves_add(&result, add_vec2(pos, vec2(2, -1)), is_white);
	moves_add(&result, add_vec2(pos, vec2(-2, -1)), is_white);
	moves_add(&result, add_vec2(pos, vec2(1, 2)), is_white);
	moves_add(&result, add_vec2(pos, vec2(-1, 2)), is_white);
	moves_add(&result, add_vec2(pos, vec2(1, -2)), is_white);
	moves_add(&result, add_vec2(pos, vec2(-1, -2)), is_white);
	return (result);
}

t_moves	*check_diag(t_vector2 pos, t_vector2 move_strength_up, t_vector2 move_strength_down, int is_white, int take)
{
	t_moves		*result;

	result = NULL;
	move_add_move(&result, do_diag(pos, move_strength_up, move_strength_down, is_white, take, 1, 1));
	move_add_move(&result, do_diag(pos, move_strength_up, move_strength_down, is_white, take, 1, 0));
	move_add_move(&result, do_diag(pos, move_strength_up, move_strength_down, is_white, take, 0, 1));
	move_add_move(&result, do_diag(pos, move_strength_up, move_strength_down, is_white, take, 0, 0));
	return (result);
}

t_moves	*get_moves_from_pos_mouse(t_mlx *mlx, t_vector2 pos)
{
	mlx->current_piece = pos;
	return (get_moves_pieces(pos, board[pos.y][pos.x]));
}

void	move_piece(t_vector2 from, t_vector2 to)
{
	t_piece	tmp;

	tmp = board[from.y][from.x];
	board[from.y][from.x] = RIEN;
	board[to.y][to.x] = tmp;
}