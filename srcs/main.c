/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:12 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/18 06:35:44 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/chess.h"

int	_input(int keycode, t_mlx *mlx)
{
	if (keycode == K_ESC)
		mlx_loop_end(mlx->mlx);
	return (1);
}

int	_input_mouse(int keycode, int x, int y, t_mlx *mlx)
{
	t_vector2	pos;

	if (keycode == M_CLK_L)
	{
		pos.x = x / 100;
		pos.y = y / 100;
		if (check_if_move_is_played(mlx, pos) <= 0)
		{
			free_moves(mlx->possible_moves);
			mlx->possible_moves = NULL;
			mlx->possible_moves = get_moves_from_pos_mouse(mlx, pos);
		}
		else
		{
			free_moves(mlx->possible_moves);
			mlx->possible_moves = NULL;
		}
		del_images(mlx);
		new_image(mlx, vec2(800, 800), vec2(0, 0));
		draw_board(mlx, 0xe9fcf7, 0x726fa7);
		draw_pieces(mlx);
		draw_moves(mlx, mlx->possible_moves);
		put_imgs(mlx);
	}
	return (1);
}

int	main()
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->possible_moves = NULL;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, 800, 800, "chess");
	mlx->imgs[0].img = NULL;
	new_image(mlx, vec2(800, 800), vec2(0, 0));
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_mouse_hook(mlx->win, _input_mouse, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, mlx_loop_end, mlx->mlx);
	draw_board(mlx, 0xe9fcf7, 0x726fa7);
	draw_pieces(mlx);
	put_imgs(mlx);
	mlx_loop(mlx->mlx);
	del_images(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free_moves(mlx->possible_moves);
	free(mlx);
}