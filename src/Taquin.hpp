#ifndef TAQUIN_HPP
#define	TAQUIN_HPP

#include "Node.hpp"
#include "ZobristHash.hpp"
#include "utils.hpp"

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

		//Taquin_board
		void	show_board(std::vector<int> &baord);

		//Taquin_heuristics
		int		evaluation();	
		int		heuristics_manhattan_distance();
		int		heuristics_improved_manhattan_distance();
		int		heuristics_correct_number_of_pieces();
};

#endif
