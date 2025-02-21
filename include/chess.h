/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chess.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:34 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/21 15:10:16 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHESS_H
# define CHESS_H
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include "utils.h"

typedef enum
{
	RIEN = 1,
	PION_B,
	TOUR_B,
	CHEV_B,
	FOU_B,
	REIN_B,
	ROI_B,
	PION_N,
	TOUR_N,
	CHEV_N,
	FOU_N,
	REIN_N,
	ROI_N
}	t_piece;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_vector2	pos;
	t_vector2	size;
}	t_img;

typedef struct s_moves
{
	t_vector2		pos;
	struct s_moves	*next;
}	t_moves;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	int			turn;
	t_vector2	has_king_moved;
	t_vector2	has_white_rook_moved;
	t_vector2	has_black_rook_moved;
	t_vector2	check;
	t_vector2	current_piece;
	t_moves		*possible_moves;
	t_img		imgs[50000];
}	t_mlx;

////////////////////////---RENDER---//////////////////////////////////////////

void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		draw_rectangle(t_img *data, t_vector2 start, t_vector2 end, int color);
void		draw_piece(t_mlx *mlx, t_piece piece, t_vector2 pos);
void		draw_board(t_mlx *mlx, int color1, int color2);
void		draw_rectangle_no_fill(t_img *data, t_vector2 start, t_vector2 end, int color);

////////////////////////---BOARD---//////////////////////////////////////////

void		draw_pieces(t_mlx *mlx);
int			is_piece_my_color(t_vector2 pos, int is_white, t_piece **sim_board);
t_moves		*check_file(t_vector2 pos, t_vector2 move_strength, int is_white, int take, t_piece **sim_board);
t_moves		*check_line(t_vector2 pos, t_vector2 move_strength, int is_white, int take, t_piece **sim_board);
t_moves		*check_diag(t_vector2 pos, t_vector2 move_strength_up, t_vector2 move_strength_down, int is_white, int take, t_piece **sim_board);
t_moves		*get_moves_from_pos_mouse(t_mlx *mlx, t_vector2 pos);
t_moves		*pawn_eat(t_vector2 pos, int is_white, t_piece **sim_board);
t_moves		*check_horse_moves(t_vector2 pos, int is_white, t_piece **sim_board);
void		move_piece(t_mlx *mlx, t_vector2 from, t_vector2 to);
t_moves		*get_color_moves(int is_white, t_piece **sim_board);
t_vector2	get_king_pos(int is_white, t_piece **sim_board);
t_piece		**get_sim_board(t_vector2 from, t_vector2 to);
void		free_sim_board(t_piece **sim_board);

////////////////////////---IMAGES---//////////////////////////////////////////

void		del_images(t_mlx *mlx);
void		add_image(t_mlx *mlx, t_img img);
int			count_images(t_mlx *mlx);
void		put_imgs(t_mlx *mlx);
int			xpm_file_to_img(t_mlx *mlx, char *path, t_vector2 pos);
int			new_image(t_mlx *mlx, t_vector2 size, t_vector2 pos);
void		put_img_to_img(t_img *dst, t_img src, int x, int y);
t_vector2	get_pos_mouse(t_mlx *mlx);

////////////////////////---MOVES---///////////////////////////////////////////

t_moves		*new_move(t_vector2 pos);
t_moves		*moves_get_last(t_moves *start);
void		moves_add(t_moves **start, t_vector2	pos, int is_white, t_piece **sim_board);
void		draw_moves(t_mlx *mlx, t_moves *moves);
t_moves		*pion_calculate_moves(t_vector2 pos, t_piece piece);
void		move_add_move(t_moves **start, t_moves *to_add);
t_moves		*get_moves_pieces(t_vector2 pos, t_piece piece, t_piece **sim_board, int is_white);
void		free_moves(t_moves *start);
int			check_if_move_is_played(t_mlx *mlx, t_vector2 pos);
int			check_if_pressure_on_pos(t_moves *moves, t_vector2 pos);
int			check_if_check(t_mlx *mlx, int is_white, t_piece **sim_board);
void		rm_move(t_moves **start, t_moves *rm_move);
void		rm_unauthorized_moves(t_moves **moves, t_vector2 from, int is_white);
void		print_tab(t_piece **tab);

// DEBUG

void			print_moves(t_moves *stat);

#endif