/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robot <robot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:57:39 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/17 04:08:42 by robot            ###   ########.fr       */
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
	while (start->next)
		start = start->next;
	return (start);
}

void	moves_add(t_moves *start, t_vector2	pos, int is_white)
{
	t_moves	*add;

	
	if (is_piece_my_color(pos, is_white) > 1)
		return ;
	add = new_move(pos);
	if (start)
	{
		start = moves_get_last(start);
		start->next = add;
	}
	else
		start = add;
}