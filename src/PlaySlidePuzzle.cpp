/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlaySlidePuzzle.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:56:35 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/31 18:36:57 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PlaySlidePuzzle.hpp"

void	PlaySlidePuzzle::display_node(Node *n)
{
	printw("n: %d\n", n->n);

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (n->board[y * size + x] == 0)
				printw("[%2c]", ' ');
			else
				printw("[%2d]", n->board[y * size + x]);
		}
		printw("\n");
	}
}

void	PlaySlidePuzzle::add_step(Node *n)
{
	history.push_back(*n);
}

void	PlaySlidePuzzle::init()
{
	index = 0;
	limit = current_node.board.size(); 
	size = sqrt(limit);
}

int		PlaySlidePuzzle::can_move(int x, int y, std::vector<int> board)
{
	int x_pos = current_node.empty_x + x;
	int y_pos = current_node.empty_y + y;

	if (x_pos < 0 || y_pos < 0 || size <= y_pos || size <= x_pos)
		return 0;
	return 1;
}

void	PlaySlidePuzzle::move_empty(int x, int y)
{
	int		tmp;
	int		tag_index = (current_node.empty_y + y) * size + (current_node.empty_x + x);
	int		empty_index = current_node.empty_y * size + current_node.empty_x;

	tmp = current_node.board[tag_index];
	current_node.board[tag_index] = 0;
	current_node.board[empty_index] = tmp;

	current_node.empty_x += x;
	current_node.empty_y += y;
	current_node.n++;
}

void	PlaySlidePuzzle::move_step(int x, int y, std::string operation)
{
	if (can_move(x, y, current_node.board) == 1)
	{
		move_empty(x, y);
	}
}

void	PlaySlidePuzzle::start(Node node)
{
	current_node = node;

	init();
	int		c;

	initscr();
	while (1)
	{
		display_node(&current_node);
		if ((c = getch()) != ERR)	
		{
			clear();
			if (c == 'q')
				break;
			if (c == 'w')
				move_step(0, -1, "UP");
			if (c == 'a')
				move_step(-1, 0, "LEFT");
			if (c == 'd')
				move_step(1, 0, "RIGHT");
			if (c == 's')
				move_step(0, 1, "DOWN");
			
			display_node(&current_node);

			if (c == 27)
			{
				c = getch();
				clear();
				if (c == 27)
					break;
				if (c == 91)
				{
					c = getch();
					clear();
					if (c == 'A')
						move_step(0, -1, "UP");
					if (c == 'D')
						move_step(-1, 0, "LEFT");
					if (c == 'C')
						move_step(1, 0, "RIGHT");
					if (c == 'B')
						move_step(0, 1, "DOWN");
				}
			}
		}
	}
	display_node(&current_node);
	node.show();

	endwin();
	exit(0);
}
