/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pion.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robot <robot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:52:34 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/17 04:13:45 by robot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/chess.h"

t_moves	*pion_calculate_moves(t_vector2 pos, t_piece piece)
{
	t_moves	*result;

	if (piece == PION_B)
	{
		if (pos.y == 6)
			moves_add(result, add_vec2(pos, vec2(0, 2)), 1);
		moves_add(result, add_vec2(pos, vec2(0, 1)), 1);
	}
	else
	{
		if (pos.y == 1)
			moves_add(result, add_vec2(pos, vec2(0, -2)), 0);
		moves_add(result, add_vec2(pos, vec2(0, -1)), 0);
	}
}