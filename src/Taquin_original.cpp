/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin_heuristics.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:14:42 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/26 15:59:01 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Taquin.hpp"

/*
 *	SEARCH_ORIGINAL
 */
int		Taquin::heuristics_original(Node *node)
{
	int						v = 0;
	std::pair<int, int>		correct_pos;
	std::pair<int, int>		target_pos;
	int						num;
	int						index = 0;
	int						search_number;
	int						current_number;

	//check number
	for (index = 0; index < size * size - 1; index++)
	{
		//x y pos
		correct_pos = goal_board_snake[index];
		//std::cout << "y: " << correct_pos.second
		//		<< " x: " << correct_pos.first << std::endl;

		//set search
		search_number = index + 1;
		
		//set currnt
		current_number = node->board[correct_pos.second * size + correct_pos.first];
		if (current_number != search_number)
			break ;
	}

	//find number
	int x;
	int y;

	for (y = 0; y < size; y++)
	{
		for (x = 0; x < size; x++)
		{
			if (node->board[y * size + x] == search_number)
				break ;
		}
		if (node->board[y * size + x] == search_number)
			break ;
	}

	//std::cout << "find x: " << x << " Y: " << y << std::endl;

	//get dist
	int		dist = abs(x - correct_pos.first) + abs(y - correct_pos.second);

	//std::cout << dist << std::endl;
	if (index == 3)
		node->show();

	node->g = node->n;
	node->h = dist + (size * size - index) * 100;
	node->w = node->g + node->h;
	//exit(0);
	return node->w;
}
