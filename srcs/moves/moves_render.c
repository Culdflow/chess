/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 04:19:59 by robot             #+#    #+#             */
/*   Updated: 2025/02/17 21:26:45 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/chess.h"

void	draw_moves(t_mlx *mlx, t_moves *moves)
{
	while (moves)
	{
		xpm_file_to_img(mlx, "sprites/move.xpm", mul_vec2(moves->pos, vec2(100, 100)));
		moves = moves->next;
	}
}