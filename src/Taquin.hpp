/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:58:24 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/03 23:48:40 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAQUIN_HPP
#define	TAQUIN_HPP

#include "Node.hpp"
#include "ZobristHash.hpp"
#include "utils.hpp"
#include "Option.hpp"
#include "PlaySlidePuzzle.hpp"

#define	OPEN_NODE	1
#define	CLOSE_NODE	0

class	Taquin
{
	private:
		typedef std::pair<int, int>			INT_PAIR;
		typedef std::pair<long long, int>	HASH_PAIR;

	public:
		Node							*current;
		Node							*new_node;
		int								size;
		int								limit;
		std::string						input_data;

		Option							*setting;

		/***   A*   ***/
		std::priority_queue<INT_PAIR, std::vector<INT_PAIR>, std::greater<INT_PAIR> >	open_pque; 
		std::map<long long, int>														hash_map;
		std::vector<Node>																node_vec;
		std::vector<int>																isOpen_vec;
			
		std::vector<int>				goal_board;
		std::vector<INT_PAIR>			goal_board_xy;

		std::vector<INT_PAIR>			goal_board_snake;
		
		//time
		time_t							start_time;
		time_t							end_time;
	

		//Total number of states ever selected in the "opened" set 
		int								opened_nodes_num;

	public:
		ZobristHash						zh;
		PlaySlidePuzzle					psp;

		void	start(std::vector<int> _board, int _size);
		void	init(Node &node, std::vector<int> &_b, int _s);
		void	display_result(Node &node);

		void	zh_init(int len, int hands_num)
		{
			zh.init(len, hands_num);
		}

		void	expansion();

		void	generate_goal_board();
		void	move_empty(int x, int y);

		//Taquin_board
		void	show_board(std::vector<int> &baord, Node *n = NULL);
		void	show_path(Node *n);

		//Taquin_heuristics
		int		evaluation(Node *n);	
		int		heuristics_manhattan_distance(Node *n);
		int		heuristics_improved_manhattan_distance(Node *n);
		int		heuristics_correct_number_of_pieces(Node *n);
		int		heuristics_euclidean_distance(Node *n);

		int		heuristics_bonus(Node *n);

		//
		std::string		get_adopted_heuristic();

		//can solve
		void	can_solve(std::vector<int> v, int size);

		class	UnsolvableException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return ("Error: Taquin: unsolvable");
				}
		};
};

#endif
