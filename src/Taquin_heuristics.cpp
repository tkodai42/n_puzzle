/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin_heuristics.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:14:42 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/23 21:54:41 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Taquin.hpp"

/*
 *	SEARCH_MANHATTAN_DISTANCE
 */
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
	node->w = node->g + node->h;

	return v;
}

/*
 *	SEARCH_IMPROVED_MANHATTAN_DISTANCE
 */
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
	node->w = node->g + node->h;

	return v;
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
	node->w = node->g + node->h;

	return v;
}

int		Taquin::evaluation(Node *node)
{
#if 1
	g_hueristics_type = SEARCH_MANHATTAN_DISTANCE;
#endif
	if (g_hueristics_type == SEARCH_MANHATTAN_DISTANCE)
		return heuristics_manhattan_distance(node);
	if (g_hueristics_type == SEARCH_IMPROVED_MANHATTAN_DISTANCE)
		return heuristics_improved_manhattan_distance(node);
	if (g_hueristics_type == SEARCH_CORRECT_NUMBER_OF_PIECES)
		return heuristics_correct_number_of_pieces(node);

		
	show_message("not find heuristics => manhattan_distance", DEBUG_ERROR);
	return heuristics_manhattan_distance(node);
}
