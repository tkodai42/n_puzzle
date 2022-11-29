/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin_heuristics.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:14:42 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/29 17:29:01 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Taquin.hpp"

/*
 *	SEARCH_ORIGINAL
 */

std::pair<int, int>	Taquin::get_correct_pos(int num)
{
	int					x;
	int					y;
	std::pair<int, int>	ret;

	ret.first = 0;
	ret.second = 0;
	for (y = 0; y < size; y++)
	{
		for (x = 0; x < size; x++)
		{
			if (goal_board[y * size + x] == num)
			{
				ret.first = x;
				ret.second = y;
				return ret;
			}
		}
	}
	return ret;
}

std::pair<int, int>	Taquin::index_to_xy(int index)
{
	std::pair<int, int>	ret;

	ret.first = index % size;
	ret.second = index / size;
	return ret;
}

std::pair<int, int>	Taquin::get_currnt_pos(int num, Node *n)
{
	int					x;
	int					y;
	std::pair<int, int>	ret;

	ret.first = 0;
	ret.second = 0;
	for (y = 0; y < size; y++)
	{
		for (x = 0; x < size; x++)
		{
			if (n->board[y * size + x] == num)
			{
				ret.first = x;
				ret.second = y;
				return ret;
			}
		}
	}
	return ret;
}


void	show_xy(int x, int y)
{
	std::cout << "x: " << x << " y: " << y << std::endl;
}
void	show_pair(std::pair<int, int > &a)
{
	std::cout << "x: " << a.first << " y: " << a.second << std::endl;
}

int		get_dist_pair(std::pair<int, int> &a, std::pair<int, int> &b)
{
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int		is_attached(std::pair<int, int> &a, std::pair<int, int> &b)
{
	if (abs(a.first - b.first) <= 1)
		return 1;
	return (abs(a.second - b.second) <= 1);
}

/***** STEP 2 *****/

void	Taquin::step_carry_target(Node *node)
{
	std::cout << "STEP 2" << std::endl;
	node->show();
	std::pair<int, int> current_xy = get_currnt_pos(target_id, node);
	std::pair<int, int> empty_xy = std::make_pair(node->empty_x, node->empty_y);
	
	//0 is around target
	if (is_attached(current_xy, empty_xy) == 0)
	{
		node->g = node->n;
		node->h = 100000000;
		node->w = node->g + node->h;
		return ;
	}
	//target to correct pos
	int dist = get_dist_pair(current_xy, correct_xy);

	if (dist == 0)
	{
		open_pque = open_queue_type();//init
		node->g = 0;//node->n;
		node->h = 10;
		node->w = node->g + node->h;
		step = STEP_0_SELECT_TARGET;
		update_step = 1;
		is_solved[target_id] = 1;
		return ;
	}

	node->g = node->n;
	node->g = 0;
	node->h = dist;
	node->w = node->g + node->h;
	//exit(0);
}

/***** STEP 1 *****/

void	Taquin::step_reach_target(Node *node)
{
	std::pair<int, int> current_xy = get_currnt_pos(target_id, node);
	int					dist;
	std::pair<int, int> empty_xy = std::make_pair(node->empty_x, node->empty_y);
	
	dist = get_dist_pair(current_xy, empty_xy);

	node->g = node->n;
	node->h = dist;
	node->w = node->g + node->h;
	//node->show();

	if (dist == 1)
	{
		//open_pque.clear();
		open_pque = open_queue_type();
		step = STEP_2_CARRY_TARGET;
		update_step = 1;
	}
}

/***** STEP 0 *****/

void	Taquin::inc_solve_len(Node *node)
{
	//increment solved_len
	std::pair<int, int>	target_pos;
	int					pos;

	if (target_group.size() == size * size)
	{
		step = STEP_7_SOLVE_SLIDE_PUZZLE;
		std::cout << "Final Step" << std::endl;
		return ;
	}

	for (int i = 0; i < target_group.size(); i++)
	{
		std::cout << target_group[i] << std::endl;
		pos = target_group[i];
		target_id = goal_board[target_group[i]]; 
		if (node->board[pos] != target_id)
		{
			if (target_group.size() == 2)
			{
				step = STEP_3_REACH_REVTARGET;
				target_id = goal_board[target_group[1]];
				correct_xy = index_to_xy(target_group[0]);
				return ;
			}
			else
			{
				step = STEP_1_REACH_TARGET;
				target_id = goal_board[target_group[0]];
				correct_xy = index_to_xy(target_group[0]);
				//std::cout << step << " " << target_id << std::endl;
				return ;
			}
		}
	}
	//set
	for (int i = 0; i < target_group.size(); i++)
		is_solved[target_group[i]] = 1;
	solved_len++;
}

void	Taquin::step_select_target(Node *node)
{
	while (1)
	{
		target_group = solve_order_board[solved_len];
		inc_solve_len(node);
		if (step != STEP_0_SELECT_TARGET)
			break ;
	}
}

int		Taquin::heuristics_original(Node *node)
{
	//distribute step
	if (step == STEP_0_SELECT_TARGET)
		step_select_target(node);
	if (step == STEP_1_REACH_TARGET)
		step_reach_target(node);
	if (step == STEP_2_CARRY_TARGET)
		step_carry_target(node);
	if (step == STEP_3_REACH_REVTARGET)
		;
	return node->w;
}
