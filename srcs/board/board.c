/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:15:19 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/21 18:05:40 by dfeve            ###   ########.fr       */
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
	{TOUR_N, CHEV_N, FOU_N, REIN_N, ROI_N, FOU_N, CHEV_N, TOUR_N},
	{PION_N, PION_N, PION_N, PION_N, PION_N, PION_N, PION_N, PION_N,},
	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN, RIEN},
	{PION_B, PION_B, PION_B, PION_B, PION_B, PION_B, PION_B, PION_B,},
	{TOUR_B, CHEV_B, FOU_B, REIN_B, ROI_B, FOU_B, CHEV_B, TOUR_B}
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

int	is_piece_my_color(t_vector2 pos, int is_white, t_piece **sim_board)
{
	t_piece	piece;

	piece = sim_board[pos.y][pos.x];
	if ((is_white == 1 && piece < 8 && piece > 1) || (is_white == 0 && piece >= 8))
		return (1);
	return (-1);
}

t_moves	*check_file(t_vector2 pos, t_vector2 move_strength, int is_white, int take, t_piece **sim_board)
{
	t_moves		*result;
	t_vector2	cursor;
	t_vector2	check_pos;


	result = NULL;
	cursor = vec2(0, 1);
	check_pos = add_vec2(cursor, pos);
	if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) >= 0)
	{
		while (cursor.y <= move_strength.y)
		{
			if (sim_board[check_pos.y][check_pos.x] == RIEN || take == 1)
				moves_add(&result, check_pos, is_white, sim_board);
			if (sim_board[check_pos.y][check_pos.x] != RIEN)
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
	while (cursor.y <= move_strength.x)
	{
		//printf("testing pos x: %d y: %d\n", check_pos.x, check_pos.y);
		if (sim_board[check_pos.y][check_pos.x] == RIEN || take == 1)
			moves_add(&result, check_pos, is_white, sim_board);
		if (sim_board[check_pos.y][check_pos.x] != RIEN)
			break ;
		cursor.y++;
		check_pos = sub_vec2(pos, cursor);
		if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) < 0)
			return (result);
	}
	return (result);
}

t_moves	*check_line(t_vector2 pos, t_vector2 move_strength, int is_white, int take, t_piece **sim_board)
{
	t_moves		*result;
	t_vector2	cursor;
	t_vector2	check_pos;

	result = NULL;
	cursor = vec2(1, 0);
	check_pos = add_vec2(cursor, pos);
	if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) >= 0)
	{
		while (cursor.x <= move_strength.y)
		{
			if (sim_board[check_pos.y][check_pos.x] == RIEN || take == 1)
				moves_add(&result, check_pos, is_white, sim_board);
			if (sim_board[check_pos.y][check_pos.x] != RIEN)
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
	while (cursor.x <= move_strength.x)
	{
		if (sim_board[check_pos.y][check_pos.x] == RIEN || take == 1)
			moves_add(&result, check_pos, is_white, sim_board);
		if (sim_board[check_pos.y][check_pos.x] != RIEN)
			break ;
		cursor.x++;
		check_pos = sub_vec2(pos, cursor);
		if (clamp_vec2(&check_pos, vec2(0, 0), vec2(7, 7)) < 0)
			return (result);
	}
	return (result);
}

t_moves	*do_diag(t_vector2 pos, t_vector2 move_strength_up, t_vector2 move_strength_down, int is_white, int take, int front, int inv, t_piece **sim_board)//ma fonction prefere jsp comment elle marche mais mashallah
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
		//printf("what is at the place of the king : %d\n", sim_board[1][5]);
		while (cursor.y <= move_strength_up.y)
		{
			//printf("testing place x: %d y: %d\n", check_pos.x, check_pos.y);
			if (inv == 0)
			{
				check_pos = add_vec2(cursor, pos);
				if (sim_board[check_pos.y][check_pos.x] == RIEN || take == 1)
					moves_add(&result, check_pos, is_white, sim_board);
				if (sim_board[check_pos.y][check_pos.x] != RIEN )
					break ;
			}
			else
			{
				check_pos = add_vec2(pos, vec2_inv_x(cursor));
				if (sim_board[check_pos.y][check_pos.x] == RIEN || take == 1)
					moves_add(&result, check_pos, is_white, sim_board);
				if (sim_board[check_pos.y][check_pos.x] != RIEN)
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
		while (cursor.y <= move_strength_down.y)
		{
			if (inv == 0)
			{
				if (sim_board[check_pos.y][check_pos.x] == RIEN || take == 1)
					moves_add(&result, check_pos, is_white, sim_board);
				if (sim_board[check_pos.y][check_pos.x] != RIEN)
					break ;
			}
			else
			{
				if (sim_board[check_pos.y][check_pos.x] == RIEN || take == 1)
					moves_add(&result, check_pos, is_white, sim_board);
				if (sim_board[check_pos.y][check_pos.x] != RIEN)
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

t_moves	*pawn_eat(t_vector2 pos, int is_white, t_piece **sim_board)
{
	t_moves		*result;
	t_vector2	test_pos;

	result = NULL;
	if (is_white == 1)
	{
		test_pos = sub_vec2(pos, vec2(1, 1));
		if (clamp_vec2(&test_pos, vec2(0, 0), vec2(7, 7)) > -1)
		{
			if (sim_board[test_pos.y][test_pos.x] >= 8)
				moves_add(&result, test_pos, is_white, sim_board);
		}
		test_pos = sub_vec2(pos, vec2(-1, 1));
		if (clamp_vec2(&test_pos, vec2(0, 0), vec2(7, 7)) > -1)
		{
			if (sim_board[test_pos.y][test_pos.x] >= 8)
				moves_add(&result, test_pos, is_white, sim_board);
		}
	}
	else
	{
		test_pos = add_vec2(pos, vec2(1, 1));
		if (clamp_vec2(&test_pos, vec2(0, 0), vec2(7, 7)) > -1)
		{
			if (sim_board[test_pos.y][test_pos.x] > 1 && sim_board[test_pos.y][test_pos.x] < 8)
				moves_add(&result, test_pos, is_white, sim_board);
		}
		test_pos = add_vec2(pos, vec2(-1, 1));
		if (clamp_vec2(&test_pos, vec2(0, 0), vec2(7, 7)) > -1)
		{
			if (sim_board[test_pos.y][test_pos.x] > 1 && sim_board[test_pos.y][test_pos.x] < 8)
				moves_add(&result, test_pos, is_white, sim_board);
		}
	}
	return (result);
}

t_moves	*check_horse_moves(t_vector2 pos, int is_white, t_piece **sim_board)
{
	t_moves	*result;

	result = NULL;
	moves_add(&result, add_vec2(pos, vec2(2, 1)), 	is_white, sim_board);
	moves_add(&result, add_vec2(pos, vec2(-2, 1)), 	is_white, sim_board);
	moves_add(&result, add_vec2(pos, vec2(2, -1)), 	is_white, sim_board);
	moves_add(&result, add_vec2(pos, vec2(-2, -1)), is_white, sim_board);
	moves_add(&result, add_vec2(pos, vec2(1, 2)), 	is_white, sim_board);
	moves_add(&result, add_vec2(pos, vec2(-1, 2)), 	is_white, sim_board);
	moves_add(&result, add_vec2(pos, vec2(1, -2)), 	is_white, sim_board);
	moves_add(&result, add_vec2(pos, vec2(-1, -2)), is_white, sim_board);
	return (result);
}

t_moves	*check_diag(t_vector2 pos, t_vector2 move_strength_up, t_vector2 move_strength_down, int is_white, int take, t_piece **sim_board)
{
	t_moves		*result;

	result = NULL;
	move_add_move(&result, do_diag(pos, move_strength_up, move_strength_down, is_white, take, 1, 1, sim_board));
	move_add_move(&result, do_diag(pos, move_strength_up, move_strength_down, is_white, take, 1, 0, sim_board));
	move_add_move(&result, do_diag(pos, move_strength_up, move_strength_down, is_white, take, 0, 1, sim_board));
	move_add_move(&result, do_diag(pos, move_strength_up, move_strength_down, is_white, take, 0, 0, sim_board));
	return (result);
}

t_moves	*get_castle(t_mlx *mlx, t_vector2 pos, int is_white, t_piece **sim_board)
{
	t_piece	piece;
	t_moves	*result;
	t_moves	*ennemy_moves;

	result = NULL;
	ennemy_moves = NULL;
	piece = board[pos.y][pos.x];
	if (is_white == 1 && piece == ROI_B)
	{
		ennemy_moves = get_color_moves(0, sim_board);
		if (mlx->has_king_moved.x == 0)
		{
			if (board[7][5] == RIEN && board[7][6] == RIEN && mlx->has_white_rook_moved.y == 0)
			{
				if (check_if_pressure_on_pos(ennemy_moves, vec2(5, 7)) == -1
						&& check_if_pressure_on_pos(ennemy_moves, vec2(6, 7)) == -1)
				{
					moves_add(&result, vec2(6, 7), is_white, sim_board);
					mlx->rock.y = 1;
				}
			}
			if (board[7][1] == RIEN && board[7][2] == RIEN && board[7][3] == RIEN && mlx->has_white_rook_moved.x == 0)
			{
				if (check_if_pressure_on_pos(ennemy_moves, vec2(2, 7)) == -1
							&& check_if_pressure_on_pos(ennemy_moves, vec2(3, 7)) == -1)
				{
					moves_add(&result, vec2(2, 7), is_white, sim_board);
					mlx->rock.x = 1;
				}
			}
		}
		free_moves(ennemy_moves);
	}
	else if (is_white == 0 && piece == ROI_N)
	{
		ennemy_moves = get_color_moves(1, sim_board);
		if (mlx->has_king_moved.y == 0)
		{
			if (board[0][5] == RIEN && board[0][6] == RIEN && mlx->has_black_rook_moved.y == 0)
			{
				if (check_if_pressure_on_pos(ennemy_moves, vec2(5, 0)) == -1
						&& check_if_pressure_on_pos(ennemy_moves, vec2(6, 0)) == -1)
				{
					moves_add(&result, vec2(6, 0), is_white, sim_board);
					mlx->rock.y = 1;
				}
			}
			if (board[0][1] == RIEN && board[0][2] == RIEN && board[0][3] == RIEN && mlx->has_black_rook_moved.x == 0)
			{
				if (check_if_pressure_on_pos(ennemy_moves, vec2(2, 0)) == -1
							&& check_if_pressure_on_pos(ennemy_moves, vec2(3, 0)) == -1)
				{
					moves_add(&result, vec2(2, 0), is_white, sim_board);
					mlx->rock.x = 1;
				}
			}
		}
		free_moves(ennemy_moves);
	}
	else
		mlx->rock = vec2(0, 0);
	return (result);
}

t_moves	*get_moves_from_pos_mouse(t_mlx *mlx, t_vector2 pos)
{
	t_moves	*moves;
	t_piece	**sim_board;
	int		is_white;

	moves = NULL;
	sim_board = NULL;
	is_white = 1;
	if (board[pos.y][pos.x] >= 8)
		is_white = 0;
	if (board[pos.y][pos.x] <= 1)
		return (NULL);
	if ((is_white == 0 && mlx->turn % 2 != 0) || (is_white == 1 && mlx->turn % 2 == 0))
	{
		sim_board = get_sim_board(vec2(0,0), vec2(0,0));
		mlx->current_piece = pos;
		moves = get_moves_pieces(pos, board[pos.y][pos.x], sim_board, is_white);
		rm_unauthorized_moves(&moves, pos, is_white);
		move_add_move(&moves, get_castle(mlx, pos, is_white, sim_board));
		free_sim_board(sim_board);
		return (moves);
	}
	return (NULL);
}

void	check_if_king_or_rook_moved(t_mlx *mlx, t_piece piece, t_vector2 pos)
{
	if (piece == ROI_B)
		mlx->has_king_moved.x = 1;
	if (piece == ROI_N)
		mlx->has_king_moved.y = 1;
	if (piece == TOUR_B)
	{
		if (compare_vec2(pos, vec2(7, 7)))
			mlx->has_white_rook_moved.y = 1;
		if (compare_vec2(pos, vec2(0, 7)))
			mlx->has_white_rook_moved.x = 1;
	}
	if (piece == TOUR_N)
	{
		if (compare_vec2(pos, vec2(0, 0)))
			mlx->has_white_rook_moved.x = 1;
		if (compare_vec2(pos, vec2(7, 0)))
			mlx->has_white_rook_moved.y = 1;
	}
}

void	move_piece(t_mlx *mlx, t_vector2 from, t_vector2 to)
{
	t_piece	tmp;

	if (mlx)
		check_if_king_or_rook_moved(mlx, board[from.y][from.x], from);
	tmp = board[from.y][from.x];
	board[from.y][from.x] = RIEN;
	if (tmp == PION_B && to.y == 0)
		board[to.y][to.x] = REIN_B;
	else if (tmp == PION_N && to.y == 7)
		board[to.y][to.x] = REIN_N;
	else
		board[to.y][to.x] = tmp;
}

t_moves	*get_color_moves(int is_white, t_piece **sim_board)
{
	t_vector2	cursor;
	t_moves		*result;

	result = NULL;
	cursor = vec2(0, 0);
	while (cursor.y < 8)
	{
		cursor.x = 0;
		while (cursor.x < 8)
		{
			int piece = sim_board[cursor.y][cursor.x];
			if (piece > 1)
			{
				if ((is_white == 1 && piece < 8) \
						|| (is_white == 0 && piece >= 8)) {
							t_moves *moves = get_moves_pieces(cursor, piece, sim_board, is_white);
							move_add_move(&result, moves);
						}
			}
			cursor.x++;
		}
		cursor.y++;
	}
	return (result);
}

t_vector2	get_king_pos(int is_white, t_piece **sim_board)
{
	t_vector2	cursor;

	cursor = vec2(0, 0);
	while (cursor.y < 8)
	{
		cursor.x = 0;
		while (cursor.x < 8)
		{
			if (!sim_board)
			{
				if ((is_white == 1 && board[cursor.y][cursor.x] == ROI_B) || (is_white == 0 && board[cursor.y][cursor.x] == ROI_N))
					return (cursor);
			}
			else
			{
				if ((is_white == 1 && sim_board[cursor.y][cursor.x] == ROI_B) || (is_white == 0 && sim_board[cursor.y][cursor.x] == ROI_N))
					return (cursor);
			}
			cursor.x++;
		}
		cursor.y++;
	}
	return (vec2(0, 0));
}

t_piece	**get_sim_board(t_vector2 from, t_vector2 to)
{
	t_piece		**sim_board;
	t_vector2	cursor;

	cursor = vec2(0, 0);
	sim_board = malloc(sizeof(t_piece *) * 9);
	while (cursor.y < 8)
	{
		cursor.x = 0;
		sim_board[cursor.y] = malloc(sizeof(t_piece) * 9);
		while (cursor.x < 8)
		{
			sim_board[cursor.y][cursor.x] = board[cursor.y][cursor.x];
			cursor.x++;
		}
		cursor.y++;
	}
	if (!compare_vec2(from, to))
	{
		sim_board[to.y][to.x] = sim_board[from.y][from.x];
		sim_board[from.y][from.x] = RIEN;
	}
	return (sim_board);
}

void	free_sim_board(t_piece **sim_board)
{
	int	x;

	x = 0;
	while (x < 8)
		free(sim_board[x++]);
	free(sim_board);
}