/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:57:39 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/21 18:03:50 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/chess.h"

t_moves	*new_move(t_vector2 pos)
{
	t_moves	*result;

	result = malloc(sizeof(t_moves));
	result->next = NULL;
	result->pos = pos;
	return (result);
}

t_moves	*moves_get_last(t_moves *start)
{
	if (!start)
		return (NULL);
	while (start->next)
		start = start->next;
	return (start);
}

void	moves_add(t_moves **start, t_vector2 pos, int is_white, t_piece **sim_board)
{
	t_moves	*add;
	t_moves	*new_start;

	new_start = *start;
	if (clamp_vec2(&pos, vec2(0, 0), vec2(7, 7)) < 0)
		return ;
	if (is_piece_my_color(pos, is_white, sim_board) > 0)
		return ;
	add = new_move(pos);
	if (!start || !(*start))
	{
		*start = add;
		return ;
	}
	new_start = moves_get_last(*start);
	new_start->next = add;
}

void	move_add_move(t_moves **start, t_moves *to_add)
{
	t_moves	*tmp;

	tmp = *start;
	if (!start || !(*start))
	{
		*start = to_add;
		return ;
	}
	tmp = moves_get_last(tmp);
	tmp->next = to_add;
}

void	free_moves(t_moves *start)
{
	t_moves	*tmp;

	while (start)
	{
		tmp = start->next;
		free(start);
		start = tmp;
	}
}

void	rm_move(t_moves **start, t_moves *rm_move)
{
	int		pos;
	int		cursori;
	t_moves	*cursor;
	t_moves	*tmp;

	pos = 0;
	cursori = 0;
	cursor = *start;
	tmp = NULL;
	if (!cursor || !rm_move)
		return ;
	while (cursor)
	{
		if (compare_vec2(rm_move->pos, cursor->pos))
			break;
		cursor = cursor->next;
		pos++;
	}
	cursor = *start;
	if (pos == 0)
	{
		if (cursor->next)
			*start = cursor->next;
		else
			*start = NULL;
		free(cursor);
		return ;
	}
	while (cursor)
	{
		if (cursori == pos - 1)
		{
			tmp = cursor->next;
			if (cursor->next->next)
				cursor->next = tmp->next;
			else
				cursor->next = NULL;
			free(tmp);
		}
		cursor = cursor->next;
		cursori++;
	}
}

int	check_if_move_is_played(t_mlx *mlx, t_vector2 pos)
{
	t_moves	*cursor;

	cursor = mlx->possible_moves;
	while (cursor)
	{
		if (compare_vec2(pos, cursor->pos))
		{
			if (!compare_vec2(mlx->en_passant_victim, vec2(-1, -1)))
			{
				if ((get_piece_from_pos(NULL, pos) < 8 && get_piece_from_pos(NULL, mlx->en_passant_victim) < 8)
						&& (get_piece_from_pos(NULL, pos) >= 8 && get_piece_from_pos(NULL, mlx->en_passant_victim) >= 8))
					mlx->en_passant_victim = vec2(-1, -1);
			}
			if (mlx->rock.x == 1 && abs(mlx->current_piece.x - pos.x) > 1)
			{
				move_piece(mlx, vec2(0, pos.y), vec2(3, pos.y), NULL);
				mlx->rock.x = 0;
			}
			else if (mlx->rock.y == 1 && abs(mlx->current_piece.x - pos.x) > 1)
			{
				move_piece(mlx, vec2(7, pos.y), vec2(5, pos.y), NULL);
				mlx->rock.y = 0;
			}
			if ((get_piece_from_pos(NULL, mlx->current_piece) == PION_B || get_piece_from_pos(NULL, mlx->current_piece) == PION_N)
						&& (abs(mlx->current_piece.y - pos.y) > 1))
						mlx->en_passant_victim = pos;
			else if ((mlx->current_piece.x != pos.x) && get_piece_from_pos(NULL, pos) == RIEN 
					&& (get_piece_from_pos(NULL, mlx->current_piece) == PION_B || get_piece_from_pos(NULL, mlx->current_piece) == PION_N)
						&& !compare_vec2(mlx->en_passant_victim, vec2(-1, -1)))
				replace_piece_from_board(NULL, mlx->en_passant_victim, RIEN);
			move_piece(mlx, mlx->current_piece, pos, NULL);
			return (1);
		}
		cursor = cursor->next;
	}
	return (-1);
}

int	check_if_pressure_on_pos(t_moves *moves, t_vector2 pos)
{
	while (moves)
	{
		if (compare_vec2(pos, moves->pos))
			return (1);
		moves = moves->next;
	}
	return (-1);
}
void	print_tab(t_piece **tab)
{
	t_vector2	cursor;

	cursor = vec2(0, 0);
	while (cursor.y < 8)
	{
		cursor.x = 0;
		while (cursor.x < 8)
		{
			printf("-%d-", tab[cursor.y][cursor.x]);
			cursor.x++;
		}
		printf("\n");
		cursor.y++;
	}
}

void	print_moves(t_moves *stat)
{
	while (stat)
	{
		printf("pos y: %d x:%d\n", stat->pos.y, stat->pos.x);
		stat = stat->next;
	}
}

int	check_if_check(t_mlx *mlx, int is_white, t_piece **sim_board)
{
	t_moves		*white_moves;
	t_moves		*black_moves;
	t_vector2	king_pos_w;
	t_vector2	king_pos_b;

	(void)mlx;
	black_moves = get_color_moves(mlx, 0, sim_board);
	white_moves = get_color_moves(mlx, 1, sim_board);
	king_pos_w = get_king_pos(1, sim_board);
	king_pos_b = get_king_pos(0, sim_board);
	if (is_white == 1)
	{
		if (check_if_pressure_on_pos(black_moves, king_pos_w) == 1)
		{
			free_moves(black_moves);
			free_moves(white_moves);
			return (1);
		}
	}
	else
	{
		if (check_if_pressure_on_pos(white_moves, king_pos_b) == 1)
		{
			// printf("b\n");
			free_moves(black_moves);
			free_moves(white_moves);
			return (0);
		}
	}
	free_moves(black_moves);
	free_moves(white_moves);
	return (-1);
}

void	rm_unauthorized_moves(t_mlx *mlx, t_moves **moves, t_vector2 from, int is_white)
{
	t_moves	*start;
	t_moves	*tmp;
	t_piece	**sim_board;

	start = *moves;
	while (start)
	{
		sim_board = get_sim_board(mlx, from, start->pos);
		if ((check_if_check(mlx, is_white, sim_board) == 1) || (check_if_check(mlx, is_white, sim_board) == 0))
		{
			tmp = start->next;
			rm_move(moves, start);
			start = tmp;
		}
		else
			start = start->next;
		free_sim_board(sim_board);
	}
}