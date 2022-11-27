/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin_heuristics.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:14:42 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/27 16:35:41 by tkodai           ###   ########.fr       */
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
	{
		std::vector<int>		tmp = solve_order_board[0];
		
		//select vector
		int		i;
		int		diff = 0;

		for (i = 0; i < solve_order_board.size(); i++)
		{
			tmp = solve_order_board[i];
			for (int i = 0; i < tmp.size(); i++)
			{
				if (goal_board[tmp[i]] != node->board[i])
				{
					diff = 1;
					break;
				}
			}
			if (diff == 1)
				break ;
		}

		int 					num;
		int 					v = 0;
		std::pair<int, int>		correct_pos;

		for (int i = 0; i < tmp.size(); i++)
		{
			num = node->board[tmp[i]];
			//std::cout << "tmp: " << tmp[i] << std::endl;
			//std::cout << "gol: " << goal_board[tmp[i]] << std::endl;
			if (goal_board[tmp[i]] != num)
			{
				correct_pos = get_currnt_pos(goal_board[tmp[i]], node);
				//std::cout << "> " << goal_board[tmp[i]] << std::endl;
				//std::cout << correct_pos.first << std::endl;
				//std::cout << correct_pos.second << std::endl;
				int x = tmp[i] % size;
				int y = tmp[i] / size;
				int dist = abs(x - correct_pos.first) + abs(y - correct_pos.second);
				v += dist;
				//std::cout << dist << std::endl;
			}
		}

		node->g = node->n;
		node->h = v + (size * size - i) * 100;
		//std::cout << "v " << v << " i " << i << std::endl;
		node->w = node->h;
		//if (i == 3)
		node->show();
		return v;
	}

	int						v = 0;
	std::pair<int, int>		correct_pos;
	std::pair<int, int>		target_pos;
	int						num;
	int						index = 0;
	int						search_number;
	int						current_number;

	//check number
	for (index = 0; index < size * size - 1; index++)
	{
		//x y pos
		correct_pos = goal_board_snake[index];
		//std::cout << "y: " << correct_pos.second
		//		<< " x: " << correct_pos.first << std::endl;

		//set search
		search_number = index + 1;
		
		//set currnt
		current_number = node->board[correct_pos.second * size + correct_pos.first];
		if (current_number != search_number)
			break ;
	}

	//find number
	int x;
	int y;

	for (y = 0; y < size; y++)
	{
		for (x = 0; x < size; x++)
		{
			if (node->board[y * size + x] == search_number)
				break ;
		}
		if (node->board[y * size + x] == search_number)
			break ;
	}

	//std::cout << "find x: " << x << " Y: " << y << std::endl;

	//get dist
	int		dist = abs(x - correct_pos.first) + abs(y - correct_pos.second);

	//std::cout << dist << std::endl;
	if (index == 3)
		node->show();

	node->g = node->n;
	node->h = dist + (size * size - index) * 100;
	node->w = node->g + node->h;
	//exit(0);
	return node->w;
}
