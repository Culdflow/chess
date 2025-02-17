/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robot <robot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 04:19:59 by robot             #+#    #+#             */
/*   Updated: 2025/02/17 04:46:05 by robot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/chess.h"

void	draw_moves(t_mlx *mlx, t_moves *moves)
{
	while (moves)
	{
		printf("testing move pos x: %d, y: %d\n", moves->pos.x, moves->pos.y);
		xpm_file_to_img(mlx, "sprites/move.xpm", mul_vec2(moves->pos, vec2(100, 100)));
		moves = moves->next;
	}
}