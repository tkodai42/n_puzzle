#ifndef TAQUIN_HPP
#define	TAQUIN_HPP

#include "Node.hpp"
#include "ZobristHash.hpp"

class	Taquin
{
	public:
		Node							*current;
		Node							*new_node;
		std::priority_queue<Node>		open_queue;
		std::map<unsigned int, Node>	close_map;
		int								size;

		std::vector<int>				goal_board;
		std::vector<std::pair<int, int> >	goal_board_xy;
	
	public:
		ZobristHash						zh;

		void	start(std::vector<int> _board, int _size);

		void	zh_init(int len, int hands_num)
		{
			zh.init(len, hands_num);
		}

		void	expansion();

		void	generate_goal_board();
		int		calculate_w(Node *node);
};

#endif
