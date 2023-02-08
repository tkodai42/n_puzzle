/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin_heuristics.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:14:42 by tkodai            #+#    #+#             */
/*   Updated: 2023/02/06 16:48:11 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Taquin.hpp"

void	show_xy(std::pair<int, int> x)
{
	std::cout << "x:" << x.first << " y:" << x.second << std::endl;
}

/*
 *	SEARCH_MANHATTAN_DISTANCE
 */
int		Taquin::heuristics_manhattan_distance_2(Node *node)
{
	int					old_h;
	int					new_h;
	std::pair<int, int>	correct_pos_pair;

	correct_pos_pair = goal_board_xy[target_num];
	old_h = abs(target_xy.first - correct_pos_pair.first)
			+ abs(target_xy.second - correct_pos_pair.second);	
	new_h = abs(empty_xy.first - correct_pos_pair.first)
			+ abs(empty_xy.second - correct_pos_pair.second);	
	
	node->g = node->n;
	node->h -= old_h;
	node->h += new_h;

	return heuristics_bonus(node);
}

int		Taquin::heuristics_manhattan_distance(Node *node)
{
	int					v = 0;
	std::pair<int, int>	correct_pos_pair;
	int					num;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			num = node->board[y * size + x];
			if (num == 0) //is space
				continue ;
			correct_pos_pair = goal_board_xy[num];
			v += abs(x - correct_pos_pair.first) + abs(y - correct_pos_pair.second);
		}
	}
	node->g = node->n;
	node->h = v;

	return heuristics_bonus(node);
}

/*
 *	SEARCH_IMPROVED_MANHATTAN_DISTANCE
 */

int		Taquin::heuristics_improved_manhattan_distance_2(Node *node)
{
	int					old_h;
	int					new_h;
	int					x_dist;
	int					y_dist;

	std::pair<int, int>	correct_pos_pair;

	correct_pos_pair = goal_board_xy[target_num];

	x_dist = abs(target_xy.first - correct_pos_pair.first);
	y_dist = abs(target_xy.second - correct_pos_pair.second);
	old_h = x_dist * x_dist + y_dist * y_dist;

	x_dist = abs(empty_xy.first - correct_pos_pair.first);
	y_dist = abs(empty_xy.second - correct_pos_pair.second);
	new_h = x_dist * x_dist + y_dist * y_dist;

	node->g = node->n;
	node->h -= old_h;
	node->h += new_h;

	return heuristics_bonus(node);
}

int		Taquin::heuristics_improved_manhattan_distance(Node *node)
{
	int					v = 0;
	std::pair<int, int>	correct_pos_pair;
	int					num;
	int					x_dist;
	int					y_dist;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			num = node->board[y * size + x];
			if (num == 0) //is space
				continue ;
			correct_pos_pair = goal_board_xy[num];
			x_dist = abs(x - correct_pos_pair.first);
			y_dist = abs(y - correct_pos_pair.second);
			v += x_dist * x_dist + y_dist * y_dist;
		}
	}

	node->g = node->n;
	node->h = v;

	return heuristics_bonus(node);
}

/*
 *	SEARCH_CORRECT_NUMBER_OF_PIECES
 */
int		Taquin::heuristics_correct_number_of_pieces(Node *node)
{
	int					v = 0;
	std::pair<int, int>	correct_pos_pair;
	int					num;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			num = node->board[y * size + x];
			if (num == 0) //is space
				continue ;
			correct_pos_pair = goal_board_xy[num];
			if (x != correct_pos_pair.first || y != correct_pos_pair.second)
				v += 1;
		}
	}

	node->g = node->n;
	node->h = v;

	return heuristics_bonus(node);
}

/*
 *	SEARCH_EUCLIDEAN_DISTANCE
 */
int		Taquin::heuristics_euclidean_distance(Node *node)
{
	int					v = 0;
	std::pair<int, int>	correct_pos_pair;
	int					num;
	double				x_tmp;
	double				y_tmp;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			num = node->board[y * size + x];
			if (num == 0) //is space
				continue ;
			correct_pos_pair = goal_board_xy[num];
			x_tmp = x - correct_pos_pair.first;
			y_tmp = y - correct_pos_pair.second;
			v += sqrt((x_tmp * x_tmp + y_tmp * y_tmp));
		}
	}
	node->g = node->n;
	node->h = v;

	return heuristics_bonus(node);
}

int		Taquin::heuristics_bonus(Node *node)
{
	//normal
	if (!(setting->option_bit & BIT_GREEDY) && !(setting->option_bit & BIT_UNIFORM_COST))
		return node->w = node->g + node->h;
	//both
	if (setting->option_bit & BIT_GREEDY && setting->option_bit & BIT_UNIFORM_COST)
		return node->w = 0 + 0;
	//greedy
	if (setting->option_bit & BIT_GREEDY)
		return node->w = 0 + node->h;
	//uniform cost
	if (setting->option_bit & BIT_UNIFORM_COST)
		return node->w = node->g + 0;
	return node->w = node->g + node->h;
}

std::string	Taquin::get_adopted_heuristic()
{
	std::vector<long long> heuristics_bits;

	heuristics_bits.push_back(BIT_MANHATTAN_DISTANCE);
	heuristics_bits.push_back(BIT_IMPROVED_MANHATTAN_DISTANCE);
	heuristics_bits.push_back(BIT_CORRECT_NUMBER_OF_PIECES);
	heuristics_bits.push_back(BIT_EUCLIDEAN_DISTANCE);
	heuristics_bits.push_back(BIT_ORIGINAL);
	heuristics_bits.push_back(BIT_GREEDY_IMD);
	heuristics_bits.push_back(BIT_UNIFORM_COST);
	heuristics_bits.push_back(BIT_GREEDY);

	for (unsigned long i = 0; i < heuristics_bits.size(); i++)
	{
		if (setting->option_bit & heuristics_bits[i])
			return setting->option_name_map[heuristics_bits[i]];
	}
	return "???";
}

int		Taquin::evaluation(Node *node)
{
	if (node->n > 0)
	{
		// n > 0
		if (setting->option_bit & BIT_MANHATTAN_DISTANCE)
			return heuristics_manhattan_distance_2(node);
		if (setting->option_bit & BIT_IMPROVED_MANHATTAN_DISTANCE)
			return heuristics_improved_manhattan_distance_2(node);
	/*	if (setting->option_bit & BIT_CORRECT_NUMBER_OF_PIECES)
			return heuristics_correct_number_of_pieces_2(node);
		if (setting->option_bit & BIT_EUCLIDEAN_DISTANCE)
			return heuristics_euclidean_distance_2(node);
		if (setting->option_bit & BIT_ORIGINAL)
			return heuristics_original_2(node);*/
	}

	//first evaluation
	if (setting->option_bit & BIT_MANHATTAN_DISTANCE)
		return heuristics_manhattan_distance(node);
	if (setting->option_bit & BIT_IMPROVED_MANHATTAN_DISTANCE)
		return heuristics_improved_manhattan_distance(node);
	if (setting->option_bit & BIT_CORRECT_NUMBER_OF_PIECES)
		return heuristics_correct_number_of_pieces(node);
	if (setting->option_bit & BIT_EUCLIDEAN_DISTANCE)
		return heuristics_euclidean_distance(node);
	if (setting->option_bit & BIT_ORIGINAL)
		return heuristics_original(node);
	
	return heuristics_manhattan_distance(node);
}

