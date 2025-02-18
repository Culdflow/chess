/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pion.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:52:34 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/17 21:38:01 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/chess.h"

t_moves	*pion_calculate_moves(t_vector2 pos, t_piece piece)
{
	t_moves	*result;
	t_moves	*tmp;

	tmp = NULL;
	result = NULL;
	if (piece == PION_B)
	{
		moves_add(&result, add_vec2(pos, vec2(0, -1)), 1);
		if (pos.y == 6 && result)
			moves_add(&result, add_vec2(pos, vec2(0, -2)), 1);
	}
	else
	{
		moves_add(&result, add_vec2(pos, vec2(0, 1)), 0);
		if (pos.y == 1 && result)
			moves_add(&result, add_vec2(pos, vec2(0, 2)), 0);
	}
	return (result);
}