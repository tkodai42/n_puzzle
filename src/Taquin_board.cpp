/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin_board.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:34:14 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/29 17:16:38 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Taquin.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

void	set_next_xy(int &x, int &y)
{
	if (x == 1)
	{
		x = 0;
		y = 1;
	}
	else if (y == 1)
	{
		x = -1;
		y = 0;
	}
	else if (x == -1)
	{
		x = 0;
		y = -1;
	}
	else // y == -1
	{
		x = 1;
		y = 0;
	}
}

void	Taquin::generate_goal_board()
{
	std::vector<int>	check;
	int					x = 0;
	int					y = 0;
	int					move_x = 1;
	int					move_y = 0;
	int					tmp_x;
	int					tmp_y;
	int					next_flag;

	/* solve order */
	std::vector<int>	order_sep_vec;
	std::vector<int>	order_side_vec;
						order_side_vec.reserve(limit);
	
	this->goal_board.assign(limit, 0);
	this->goal_board_xy.resize(limit);//xy
	this->goal_board_snake.resize(limit);//xy
	check.assign(limit, 0);


	int		i = 1;

	for (; i < limit; i++)
	{
		check[y * this->size + x] = 1;
		goal_board[y * this->size + x] = i;

		goal_board_xy[i] = std::make_pair(x, y);
		goal_board_snake[i - 1] = std::make_pair(x, y);
		//original
		order_side_vec.push_back(y * this->size + x);

		next_flag = 0;
		tmp_x = x + move_x;
		tmp_y = y + move_y;
		
		if (tmp_x < 0 || tmp_y < 0 || this->size <= tmp_x || this->size <= tmp_y) //out
			next_flag = 1;
		else if (check[tmp_y * this->size + tmp_x] != 0) //already set
			next_flag = 1;
		if (next_flag == 1)
		{
			set_next_xy(move_x, move_y);
			tmp_x = x + move_x;
			tmp_y = y + move_y;
			//original
			if (i < limit - 8)
			{
				std::vector<int>	group;
				//4 => 1, 3
				//5 => 1, 1, 3
				for (int j = 0; j < order_side_vec.size(); j++)
				{
					group.push_back(order_side_vec[j]);
					if (order_side_vec.size() - j <= 2)
						;
					else
					{
						solve_order_board.push_back(group);
						group.clear();
					}
				}
				solve_order_board.push_back(group);
				group.clear();
				//solve_order_board.push_back(order_side_vec);
				order_side_vec.clear();
			}
		}
		x = tmp_x;
		y = tmp_y;
	}
	// set 0
	goal_board_xy[0] = std::make_pair(x, y);
	goal_board_snake[i - 1] = std::make_pair(x, y);
	//original
	order_side_vec.push_back(y * this->size + x);
	solve_order_board.push_back(order_side_vec);

	//for (int i = 0; i < solve_order_board.size(); i++)
	//{
	//	std::cout << solve_order_board[i].size() << std::endl;
	//}
	/*** init original ***/
	step = STEP_0_SELECT_TARGET;
	is_solved.assign(size * size, 0);
	solved_len = 0;

	//exit(0);
}

void	Taquin::show_board(std::vector<int> &board, Node *node)
{
	if (setting->option_bit & BIT_VISUALIZE)
	{
		for (int i = 0; i < limit; i++)
		{
			std::cout << board[i] << ", ";
		}
		std::cout << std::endl;
		return ;
	}

	if (node)
	{
		std::cout
			<< "n: " << node->n << " g: " << node->g << " h: " << node->h << " w: " << node->w
			<< " hash: " << node->hash << std::endl;
	}

	int	num;
	int display_width;

	if (size <= 3)
		display_width = 1;
	else if (size <= 10)
		display_width = 2;
	else
		display_width = 3;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			num = board[y * size + x];
			if (num == 0)
				std::cout << "[" << std::setw(display_width) << " " << "]";			
			else if (this->goal_board[y * size + x] == num)
			{
				std::cout << "[" << COUT_GREEN << std::setw(display_width) << num << COUT_END << "]"; 
			}
			else
				std::cout << "[" << COUT_RED << std::setw(display_width) << num << COUT_END << "]"; 
		}
		std::cout << std::endl;
	}
}

void	Taquin::show_path(Node *node)
{
	std::vector<int>	path_id;
	int					current_id = node->id;

	while (current_id != 0)
	{
		path_id.push_back(current_id);
		current_id = node_vec[current_id].parent_id;
	}
	path_id.push_back(current_id);

	std::vector<int>::reverse_iterator	r_it = path_id.rbegin();
	std::vector<int>::reverse_iterator	r_ite = path_id.rend();

	Node	tmp;

	for (int i = 0; r_it != r_ite; r_it++, i++)
	{
		tmp = node_vec[*r_it];
		show_board(tmp.board, &tmp);
	}
}
