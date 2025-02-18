/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:57:39 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/18 06:32:46 by dfeve            ###   ########.fr       */
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

void	moves_add(t_moves **start, t_vector2 pos, int is_white)
{
	t_moves	*add;
	t_moves	*new_start;

	new_start = *start;
	if (clamp_vec2(&pos, vec2(0, 0), vec2(7, 7)) < 0)
		return ;
	if (is_piece_my_color(pos, is_white) > 0)
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

int	check_if_move_is_played(t_mlx *mlx, t_vector2 pos)
{
	t_moves	*cursor;

	cursor = mlx->possible_moves;
	while (cursor)
	{
		if (compare_vec2(pos, cursor->pos))
		{
			move_piece(mlx->current_piece, cursor->pos);
			return (1);
		}
		cursor = cursor->next;
	}
	return (-1);
}