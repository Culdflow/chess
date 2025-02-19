/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:12 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/19 15:36:56 by dfeve            ###   ########.fr       */
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
	t_moves		*white_moves;
	t_moves		*black_moves;
	t_piece		**sim_board;

	white_moves = NULL;
	black_moves = NULL;
	if (keycode == M_CLK_L)
	{
		pos.x = x / 100;
		pos.y = y / 100;
		//check_if_check(mlx, NULL);
		sim_board = get_sim_board(vec2(0, 0), vec2(0, 0));
		white_moves = get_color_moves(1, sim_board);
		black_moves = get_color_moves(0, sim_board);
		if ((!white_moves && mlx->turn % 2 == 0) || (!black_moves && mlx->turn % 2 != 0))
			printf("CHECKMATE!!!\n");
		free_moves(black_moves);
		free_moves(white_moves);
		free_sim_board(sim_board);
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
			mlx->turn++;
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
	mlx->check = vec2(0, 0);
	mlx->turn = 0;
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

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////---------------------------------TO DO-----------------------------------------/////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
/////************TURN BASED*****************************************////////////////////////////////////
/////------------ADD CHECKMATE--------------------------------------////////////////////////////////////
/////------------ADD CASTLING---------------------------------------////////////////////////////////////
/////------------ADD PINNING AND PIECES NOT BEING ABLE TO MOVE------////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////