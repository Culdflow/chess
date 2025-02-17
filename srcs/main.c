/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:12 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/17 01:33:09 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/chess.h"

int	_input(int keycode, t_mlx *mlx)//Manage keyboard input
{
	if (keycode == K_ESC)
		mlx_loop_end(mlx->mlx);
	return (1);
}

int	main()
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, 800, 800, "chess");
	mlx->imgs[0].img = NULL;
	new_image(mlx, vec2(800, 800), vec2(0, 0));
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, mlx_loop_end, mlx->mlx);
	draw_board(mlx, 0xe9fcf7, 0x726fa7);
	draw_pieces(mlx);
	put_imgs(mlx);
	mlx_loop(mlx->mlx);
}