/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:19:52 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/16 20:55:40 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/chess.h"

void	clamp(int *num, int min, int max)
{
	if (min < max)
		return ;
	if (*num > max)
		*num = max;
	else if (*num < min)
		*num = min;
}

t_vector2	mul_vec2(t_vector2 vec1, t_vector2 vec2)//Returns vec1 * vec2
{
	t_vector2	result;

	result.x = vec1.x * vec2.x;
	result.y = vec1.y * vec2.y;
	return (result);
}

void	clamp_vec2(t_vector2 *vec, t_vector2 min, t_vector2 max)
{
	clamp(&vec->x, min.x, max.x);
	clamp(&vec->y, min.y, max.y);
}

int	compare_vec2(t_vector2 vec1, t_vector2 vec2)
{
	return (vec1.x == vec2.x && vec1.y == vec2.y);
}