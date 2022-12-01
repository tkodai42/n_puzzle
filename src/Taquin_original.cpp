/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin_heuristics.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:14:42 by tkodai            #+#    #+#             */
/*   Updated: 2022/12/02 03:22:31 by tkodai           ###   ########.fr       */
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

int		Taquin::xy_to_index(std::pair<int, int> &x)
{
	return x.second * size + x.first;
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
	if (abs(a.first - b.first) > 1)
		return 0;
	if (abs(a.second - b.second) > 1)
		return 0;
	return 1;
}

/***** STEP 6 *****/

void	Taquin::step_slide_two_number(Node *node)
{
	int		pos_a = xy_to_index(garage_xy);
	int		pos_b = xy_to_index(correct_xy);
	int		v = 0;

	if (node->board[pos_a] != goal_board[pos_a])
		v += 10;
	if (node->board[pos_b] != goal_board[pos_b])
		v += 10;
	
	node->g = node->n;
	node->h = v;
	node->w = node->g + node->h;
	if (v == 0)
	{
		node->h = 10;
		node->w = node->g + node->h;
		open_pque = open_queue_type();
		is_solved[target_id] = 1;
		is_solved[target_id2] = 1;
		update_step = 1;
		step = STEP_0_SELECT_TARGET;
	}
}
/***** STEP 5 *****/

void	Taquin::step_reach_garage(Node *node)
{
	std::pair<int, int> current_xy = garage_xy;
	int					dist;
	std::pair<int, int> empty_xy = std::make_pair(node->empty_x, node->empty_y);
	
	dist = get_dist_pair(current_xy, empty_xy);

	node->g = node->n;
	node->g = 0;
	node->h = dist;
	node->w = node->g + node->h;

	if (dist == 0)
	{
		//open_pque.clear();
		open_pque = open_queue_type();
		step = STEP_6_SLIDE_TWO_NUMBER;
		is_solved[target_id] = 0;
		is_solved[target_id2] = 0;
		update_step = 1;
	}
}
/***** STEP 4 *****/

void	Taquin::step_carry_rev_target(Node *node)
{
	int					_target_id;
	std::pair<int, int>	_correct_xy;

	if (garage_step == 0)
	{
		_target_id = target_id;
		_correct_xy = correct_xy;
	}
	else
	{
		_target_id = target_id2;
		_correct_xy = correct_xy2;
	}

	std::pair<int, int> current_xy = get_currnt_pos(_target_id, node);
	std::pair<int, int> empty_xy = std::make_pair(node->empty_x, node->empty_y);

	//0 is around target
	if (is_attached(current_xy, empty_xy) == 0)
	{
		node->g = node->n;
		node->h = 10000000;
		node->w = node->g + node->h;
		return ;
	}
	//target to correct pos
	int dist = get_dist_pair(current_xy, _correct_xy);

	if (dist == 0)
	{
		open_pque = open_queue_type();//init
		node->g = 0;//node->n;
		node->h = 10;
		node->w = node->g + node->h;
		is_solved[_target_id] = 1;
		update_step = 1;
		garage_step++;
		if (garage_step == 2)
		{
			step = STEP_5_REACH_GARAGE;
			return ;
		}
		step = STEP_3_REACH_REVTARGET;
		return ;
	}

	node->g = node->n;
	node->g = 0;
	node->h = dist;
	node->w = node->g + node->h;
	//exit(0);
}

/***** STEP 3 *****/

void	Taquin::step_reach_rev_target(Node *node)
{
	int		_target_id;

	if (garage_step == 0)
		_target_id = target_id;
	else
		_target_id = target_id2;

	std::pair<int, int> current_xy = get_currnt_pos(_target_id, node);
	int					dist;
	std::pair<int, int> empty_xy = std::make_pair(node->empty_x, node->empty_y);
	
	dist = get_dist_pair(current_xy, empty_xy);

	node->g = node->n;
	node->g = 0;
	node->h = dist;
	node->w = node->g + node->h;

	if (dist == 1)
	{
		//open_pque.clear();
		open_pque = open_queue_type();
		step = STEP_4_CARRY_REVTARGET;
		update_step = 1;
	}
}

/***** STEP EXCEPTION2 *****/

void	Taquin::step_exception2(Node *node)
{
	int					_target_id;
	std::pair<int, int>	_correct_xy;

	_target_id = target_id2;
	_correct_xy = correct_xy2;

	std::pair<int, int> current_xy = get_currnt_pos(_target_id, node);
	std::pair<int, int> empty_xy = std::make_pair(node->empty_x, node->empty_y);

	_correct_xy = goal_board_xy[0];

	//0 is around target
	if (is_attached(current_xy, empty_xy) == 0)
	{
		node->g = node->n;
		node->h = 10000000;
		node->w = node->g + node->h;
		return ;
	}
	//target to correct pos
	int dist = get_dist_pair(current_xy, _correct_xy);

	if (dist == 0)
	{
		open_pque = open_queue_type();//init
		node->g = 0;//node->n;
		node->h = 10;
		node->w = node->g + node->h;
		update_step = 1;
		step = STEP_3_REACH_REVTARGET;
		return ;
	}

	node->g = node->n;
	node->g = 0;
	node->h = dist;
	node->w = node->g + node->h;
	//exit(0);
}
/***** STEP EXCEPTION *****/

void	Taquin::step_exception(Node *node)
{
	int		_target_id;

	_target_id = target_id2;

	std::pair<int, int> current_xy = get_currnt_pos(_target_id, node);
	int					dist;
	std::pair<int, int> empty_xy = std::make_pair(node->empty_x, node->empty_y);
	
	dist = get_dist_pair(current_xy, empty_xy);

	node->g = node->n;
	node->g = 0;
	node->h = dist;
	node->w = node->g + node->h;

	if (dist == 1)
	{
		//open_pque.clear();
		open_pque = open_queue_type();
		step = STEP_10_EXCEPTION_ROW2;
		update_step = 1;
	}
}

/***** STEP 2 *****/

void	Taquin::step_carry_target(Node *node)
{
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
	node->g = 0;
	node->h = dist;
	node->w = node->g + node->h;

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

	if (target_group.size() == 9)
	{
		step = STEP_7_SOLVE_SLIDE_PUZZLE;

		open_pque = open_queue_type();
		update_step = 1;
		return ;
	}

	for (int i = 0; i < target_group.size(); i++)
	{
		pos = target_group[i];
		target_id = goal_board[target_group[i]]; 
		if (node->board[pos] != target_id)
		{
			if (target_group.size() == 2)
			{
				//unlock
				is_solved[goal_board[target_group[0]]] = 0;
				is_solved[goal_board[target_group[1]]] = 0;

				// ...5. -> ...45  ...AC
				// ...4.    .....  ...B.

				// set A
				step = STEP_3_REACH_REVTARGET;
				target_id = goal_board[target_group[1]];
				correct_xy = index_to_xy(target_group[0]);

				// set C
				garage_xy = index_to_xy(target_group[1]);

				// set B
				{
					target_id2 = goal_board[target_group[0]];
					//candidate
					int		candidates_x[4];
					int		candidates_y[4];
					int		center_x = target_group[0] % size;
					int		center_y = target_group[0] / size;
					int		candidate_x;
					int		candidate_y;
					int		candidate;

					//up
					candidates_x[0] = center_x;
					candidates_y[0] = center_y - 1;
					//down
					candidates_x[1] = center_x;
					candidates_y[1] = center_y + 1;
					//left
					candidates_x[2] = center_x - 1;
					candidates_y[2] = center_y;
					//right
					candidates_x[3] = center_x + 1;
					candidates_y[3] = center_y;
					
					for (int i = 0; i < 4; i++)
					{
						candidate_x = candidates_x[i];
						candidate_y = candidates_y[i];
						candidate = candidate_y * size + candidate_x;
						if (candidate_x < 0 || candidate_y < 0) //out of board
							continue ;
						if (candidate_x >= size || candidate_y >= size)
							continue ;
						if (candidate == target_group[1]) //is C
							continue ;
						if (is_solved[goal_board[candidate]] == 1)
							continue ;
						break ;
					}
					correct_xy2 = index_to_xy(candidate);
				}


				std::pair<int, int> target_xy = get_currnt_pos(target_id, node);
				int dist = get_dist_pair(target_xy, correct_xy);

				garage_step = 0;//target 1
				if (dist == 0)//target 2
				{
					garage_step = 1;
				}
				step = STEP_3_REACH_REVTARGET;
				update_step = 1;
				if (i == 1)
				{
					step = STEP_9_EXCEPTION_ROW;
				}
				return ;
			}
			else
			{
				update_step = 1;
				step = STEP_1_REACH_TARGET;
				target_id = goal_board[target_group[0]];
				correct_xy = index_to_xy(target_group[0]);
				return ;
			}
		}
	}
	//set
	for (int i = 0; i < target_group.size(); i++)
	{
		is_solved[goal_board[target_group[i]]] = 1;
	}
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
		step_reach_rev_target(node);
	if (step == STEP_4_CARRY_REVTARGET)
		step_carry_rev_target(node);
	if (step == STEP_5_REACH_GARAGE)
		step_reach_garage(node);
	if (step == STEP_6_SLIDE_TWO_NUMBER)
		step_slide_two_number(node);
	if (step == STEP_7_SOLVE_SLIDE_PUZZLE)
	{
		heuristics_manhattan_distance(node);
		step = STEP_8_SOLVE_SLIDE_PUZZLE2;
	}
	else if (step == STEP_8_SOLVE_SLIDE_PUZZLE2)
	{
		heuristics_manhattan_distance_2(node);
	}
	if (step == STEP_9_EXCEPTION_ROW)
	{
		step_exception(node);
	}
	if (step == STEP_10_EXCEPTION_ROW2)
	{
		step_exception2(node);
	}
	
	return node->w;
}
