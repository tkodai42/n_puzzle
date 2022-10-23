/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin_board.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:34:14 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/23 19:56:09 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Taquin.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

void	Taquin::show_board(std::vector<int> &board, Node *node)
{
	show_message("show_board", DEBUG_FUNCTION);		

	if (node)
	{
		std::cout
			<< "n: " << node->n << " g: " << node->g << " h: " << node->h << " w: " << node->w
			<< " hash: " << node->hash << std::endl;
	}

	int size = sqrt(board.size());
	int	num;
	int display_width;

	if (size <= 3)
		display_width = 1;
	else if (size <= 10)
		display_width = 2;
	else
		display_width = 3;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			num = board[y * size + x];
			if (num == 0)
				std::cout << "[" << std::setw(display_width) << " " << "]";			
			else if (this->goal_board[y * size + x] == num)
			{
				std::cout << "[" << COUT_GREEN << std::setw(display_width) << num << COUT_END << "]"; 
			}
			else
				std::cout << "[" << COUT_RED << std::setw(display_width) << num << COUT_END << "]"; 
		}
		std::cout << std::endl;
	}
}
