/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin_board.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:34:14 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/24 18:01:34 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Taquin.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

void	Taquin::show_board(std::vector<int> &board, Node *node)
{
	//show_message("show_board", DEBUG_FUNCTION);		

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

void	Taquin::show_path(Node *node)
{
	std::vector<int>	path_id;
	int					current_id = node->id;
	int					current_hash = node->hash;

	while (current_id != 0)
	{
		path_id.push_back(current_id);
		current_id = node_vec[current_id].parent_id;
	}
	path_id.push_back(current_id);

	std::vector<int>::reverse_iterator	r_it = path_id.rbegin();
	std::vector<int>::reverse_iterator	r_ite = path_id.rend();

	Node	tmp;

	for (int i = 0; r_it != r_ite; r_it++, i++)
	{
		//std::cout << " >>> " << i << " <<< " << std::endl;
		tmp = node_vec[*r_it];
		show_board(tmp.board, &tmp);
	}
}
