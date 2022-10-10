#ifndef NODE_HPP
#define NODE_HPP

#include "utils.hpp"
#include <math.h>

class	Node
{
	public:
		int	w; //worth
		int	n; //cost

		std::vector<int>	board;
		int					empty_x;
		int					empty_y;
		unsigned int		parent_node_hash;
		unsigned int		hash;

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
};

bool operator<(const Node &_node1, const Node &_node2);

#endif
