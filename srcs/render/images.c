/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robot <robot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:16:31 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/17 04:33:23 by robot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/chess.h"

void	put_imgs(t_mlx *mlx)
{
	int	i;

	i = 1;
	while (i < count_images(mlx) && mlx->imgs[i].img)
	{
		put_img_to_img(&mlx->imgs[0], mlx->imgs[i], mlx->imgs[i].pos.x, mlx->imgs[i].pos.y);
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->imgs[0].img,
			mlx->imgs[0].pos.x, mlx->imgs[0].pos.y);
}

int	xpm_file_to_img(t_mlx *mlx, char *path, t_vector2 pos)
{
	t_img	img;
	void	*temp;

	temp = mlx_xpm_file_to_image(mlx->mlx, path, &img.size.x, &img.size.y);
	if (temp == NULL)
		return (-1);
	mlx_destroy_image(mlx->mlx, temp);
	img.img = mlx_xpm_file_to_image(mlx->mlx, path, &img.size.x, &img.size.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.pos = pos;
	add_image(mlx, img);
	return (count_images(mlx) - 1);
}

int	new_image(t_mlx *mlx, t_vector2 size, t_vector2 pos)
{
	t_img	img;

	img.img = mlx_new_image(mlx->mlx, size.x, size.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.pos = pos;
	add_image(mlx, img);
	return (count_images(mlx) - 1);
}