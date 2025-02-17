/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chess.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robot <robot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:34 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/17 04:11:54 by robot            ###   ########.fr       */
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

typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

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
	t_img		imgs[50000];
}	t_mlx;

////////////////////////---VECTOR---//////////////////////////////////////////

t_vector2	vec2(int x, int y);
t_vector2	vec2_make_start(t_vector2 start, t_vector2 end);
t_vector2	vec2_make_end(t_vector2 start, t_vector2 end);
t_vector2	add_vec2(t_vector2 vec1, t_vector2 vec2);
t_vector2	sub_vec2(t_vector2 vec1, t_vector2 vec2);
t_vector2	mul_vec2(t_vector2 vec1, t_vector2 vec2);
void		clamp_vec2(t_vector2 *vec, t_vector2 min, t_vector2 max);

////////////////////////---RENDER---//////////////////////////////////////////

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	draw_rectangle(t_img *data, t_vector2 start, t_vector2 end, int color);

////////////////////////---BOARD---//////////////////////////////////////////

void	draw_board(t_mlx *mlx, int color1, int color2);
void	draw_pieces(t_mlx *mlx);
int		is_piece_my_color(t_vector2 pos, int is_white);

////////////////////////---IMAGES---//////////////////////////////////////////

void	del_images(t_mlx *mlx);
void	add_image(t_mlx *mlx, t_img img);
int		count_images(t_mlx *mlx);
void	put_imgs(t_mlx *mlx);
int		xpm_file_to_img(t_mlx *mlx, char *path, t_vector2 pos);
int		new_image(t_mlx *mlx, t_vector2 size, t_vector2 pos);
void	put_img_to_img(t_img *dst, t_img src, int x, int y);

////////////////////////---MOVES---///////////////////////////////////////////

t_moves	*new_move(t_vector2 pos);
t_moves	*moves_get_last(t_moves *start);
void	moves_add(t_moves *start, t_vector2	pos, int is_white);
#endif