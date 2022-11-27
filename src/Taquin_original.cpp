/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin_heuristics.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:14:42 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/28 02:31:39 by tkodai           ###   ########.fr       */
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

int		Taquin::heuristics_original(Node *node)
{
	std::vector<int>	targets = solve_order_board[solved_len];
	int					target_num;
	int					target_pos;
	std::pair<int, int>	target_xy;
	int					v = 0;
	int					x;
	int					y;

	//check orderd
	for (int j = 0; j < solved_len; j++)
	{
		std::vector<int>	targets = solve_order_board[j];
		for (int i = 0; i < targets.size(); i++)
		{
			target_pos = targets[i];
			target_num = goal_board[target_pos];
			if (target_num != node->board[target_pos])
			{
				node->g = node->n;
				node->h = 100000000;
				return node->w = node->g + node->h;
			}
		}
	}

	//std::cout << targets.size() << std::endl;
	for (int i = 0; i < targets.size(); i++)
	{
		target_pos = targets[i];
		x = target_pos % size;
		y = target_pos / size;
		target_num = goal_board[y * size + x];
		if (target_num == 0)
			continue ;
		//std::cout<< "target: " << targets[i] << " num: " << target_num << std::endl;
		target_xy = get_currnt_pos(target_num, node);
	//std::cout<<"target:x "<<target_xy.first<<" y: "<< target_xy.second<<std::endl;
		v += abs(x - target_xy.first) + abs(y - target_xy.second);
	}
	node->g = node->n;
	node->h = v;
	if (v == 0)
	{
		//clear open queue
		solved_len++;
		if (solved_len == solve_order_board.size())
			;
		else
			heuristics_original(node);
	}
	node->show();
	//exit(0);
	return node->w = node->g + node->h;


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
	return node->w = node->h;
	return node->w = node->g + node->h;

}
