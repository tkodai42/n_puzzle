/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin_heuristics.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:14:42 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/26 14:42:18 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Taquin.hpp"

/*
 *	SEARCH_ORIGINAL
 */
int		Taquin::heuristics_original(Node *node)
{
	int					v = 0;
	std::pair<int, int>	correct_pos_pair;
	int					num;
	double				x_tmp;
	double				y_tmp;
	int					x;
	int					y;
	int					correct_number;
	int					i;

	for (i = 0; i < size * size; i++)
	{
		//i == correct
		correct_number = i + 1;
		if (correct_number == size * size) //0
			continue;
		
		correct_pos_pair = goal_board_snake[i];
		x = correct_pos_pair.first;
		y = correct_pos_pair.second;
		num = node->board[y * size + x];

		if (num != correct_number)
			break;
	}
	printf("CORRECT_LEN %d\n", i);
	if (correct_number != size * size)
	{
		printf("Correct num x: %d y: %d\n",
				correct_pos_pair.first, correct_pos_pair.second);
		
	}
	/*
	if (correct_number != size * size)
	{
		x_tmp = x;
		y_tmp = y;

		for (y = 0; y < size; y++)
		{
			for (x = 0; x < size; x++)
			{
				if (node->board[y * size + x] == correct_number)
					break ;
			}
		}
		std::cout << "xy" << x << ":" << y << "d" << x_tmp << ":" << y_tmp << std::endl;
		x_tmp = x - x_tmp;
		y_tmp = y - y_tmp;
		v = sqrt((x_tmp * x_tmp + y_tmp * y_tmp)) * 10;
		x_tmp = node->empty_x - x;
		y_tmp = node->empty_y - y;
		v += sqrt((x_tmp * x_tmp + y_tmp * y_tmp));

		//x_tmp = correct_pos_pair.first;
		//y_tmp = correct_pos_pair.second;

	}*/

	node->g = node->n;
	node->h = (size * size - i) * 100 + v;
	node->w = node->h;
	std::cout << node->w << " v: " << v << " c:" << i << std::endl;
	node->show();

	if (i == 1)
		exit(0);
	return node->w;
}
