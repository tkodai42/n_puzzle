/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:58:24 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/24 16:24:15 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAQUIN_HPP
#define	TAQUIN_HPP

#include "Node.hpp"
#include "ZobristHash.hpp"
#include "utils.hpp"



class	Taquin
{
	private:
		typedef std::pair<int, int>			INT_PAIR;
		typedef std::pair<long long, int>	HASH_PAIR;

	public:
		Node							*current;
		Node							*new_node;
		//std::priority_queue<Node>		open_queue;
		//std::map<unsigned int, Node>	close_map;
		int								size;

		//--- update ---

		std::priority_queue<INT_PAIR, std::vector<INT_PAIR>, std::greater<INT_PAIR> >	open_pque; 
		//std::priority_queue<INT_PAIR>	open_pque; 
		std::map<long long, int>														hash_map;
		std::vector<Node>																node_vec;
			
		std::vector<int>				goal_board;
		std::vector<INT_PAIR>			goal_board_xy;
	
	public:
		ZobristHash						zh;

		void	start(std::vector<int> _board, int _size);

		void	zh_init(int len, int hands_num)
		{
			zh.init(len, hands_num);
		}

		void	expansion();

		void	generate_goal_board();
		void	move_empty(int x, int y);
		//int		calculate_w(Node *node);

		//Taquin_board
		void	show_board(std::vector<int> &baord, Node *n = NULL);
		void	show_path(Node *n);

		//Taquin_heuristics
		int		evaluation(Node *n);	
		int		heuristics_manhattan_distance(Node *n);
		int		heuristics_improved_manhattan_distance(Node *n);
		int		heuristics_correct_number_of_pieces(Node *n);

		//test
		int		heuristics_test_42(Node *n);
};

#endif
