/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:58:24 by tkodai            #+#    #+#             */
/*   Updated: 2022/12/02 03:17:46 by tkodai           ###   ########.fr       */
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

#define STEP_0_SELECT_TARGET	0
#define STEP_1_REACH_TARGET		1
#define STEP_2_CARRY_TARGET		2
#define STEP_3_REACH_REVTARGET	3
#define STEP_4_CARRY_REVTARGET	4
#define STEP_5_REACH_GARAGE		5
#define STEP_6_SLIDE_TWO_NUMBER	6
#define STEP_7_SOLVE_SLIDE_PUZZLE	7
#define STEP_8_SOLVE_SLIDE_PUZZLE2	8
#define STEP_9_EXCEPTION_ROW		9
#define STEP_10_EXCEPTION_ROW2		10

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
		typedef std::priority_queue<INT_PAIR, std::vector<INT_PAIR>, std::greater<INT_PAIR> >	open_queue_type; 
		std::priority_queue<INT_PAIR, std::vector<INT_PAIR>, std::greater<INT_PAIR> >	open_pque; 
		std::map<long long, int>														hash_map;
		std::vector<Node>																node_vec;
		std::vector<int>																isOpen_vec;
			
		std::vector<int>				goal_board;
		std::vector<INT_PAIR>			goal_board_xy;

		std::vector<INT_PAIR>			goal_board_snake;

		/*** original ***/
		std::vector<std::vector<int> >	solve_order_board;
		int								solved_len;
		std::vector<int>				is_solved;//by index
		int								target_id;
		int								target_id2;
		INT_PAIR						correct_xy;
		INT_PAIR						correct_xy2;
		INT_PAIR						out_size_xy;
		INT_PAIR						garage_xy;
		int								step;
		std::vector<int>				target_group;
		int								update_step;
		int								garage_step;
		
		//time
		time_t							start_time;
		time_t							end_time;
	

		//Total number of states ever selected in the "opened" set 
		int								opened_nodes_num;

		/* optimization */
		int								empty_pos;
		int								target_pos;
		int								target_num;
		std::pair<int, int>				target_xy;
		std::pair<int, int>				empty_xy;

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
		int		heuristics_original(Node *n);

		int		heuristics_manhattan_distance_2(Node *n);
		int		heuristics_improved_manhattan_distance_2(Node *n);

		int		heuristics_bonus(Node *n);

		//original
		std::pair<int, int>	get_correct_pos(int num);
		std::pair<int, int>	get_currnt_pos(int num, Node *n);
		void				step_select_target(Node *node);
		void				step_reach_target(Node *node);
		void				step_reach_rev_target(Node *node);
		void				step_carry_target(Node *node);
		void				step_carry_rev_target(Node *node);
		void				step_reach_garage(Node *node);
		void				step_slide_two_number(Node *node);
		void				step_exception(Node *node);
		void				step_exception2(Node *node);
		void				inc_solve_len(Node *node);
		std::pair<int, int>	index_to_xy(int index);
		int					xy_to_index(std::pair<int, int> &a);
		int					exception_row;

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
