/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:58:04 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/23 21:58:06 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include "utils.hpp"
#include <math.h>

class	Node
{
	public:
		int	w; //worth


		int	g; // the cost of the path from the start node to n
		int	n; // step
		int	h; // the cost of the cheapest path from n to the goal


		std::vector<int>	board;
		int					empty_x;
		int					empty_y;
		long long			parent_node_hash;
		long long			hash;
		int					isOpen;
		int					id;

	public:
		void show()
		{
			int size = sqrt(board.size());
		
			std::cout << "n: " << n << " w: " << w << " hash: " << hash << std::endl;
			for (int y = 0; y < size; y++)
			{
				for (int x = 0; x < size; x++)
				{
					std::cout << board[y * size + x] << " "; 
				}
				std::cout << std::endl;
			}
		}

		void set_empty()
		{
			int size = sqrt(board.size());

			for (int y = 0; y < size; y++)
			{
				for (int x = 0; x < size; x++)
				{
					if (board[y * size + x] == 0)
					{
						empty_x = x;
						empty_y = y;
						return ;
					}
				}
			}
		}
};

bool operator<(const Node &_node1, const Node &_node2);

#endif
