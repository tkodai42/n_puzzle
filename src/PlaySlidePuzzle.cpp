/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlaySlidePuzzle.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:56:35 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/01 16:49:49 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PlaySlidePuzzle.hpp"

void	PlaySlidePuzzle::display_node(Node *n)
{
	printw("\n step: %d\n\n", n->n);

	int		num;
	int		right_pos_count = 0;

	for (int y = 0; y < size; y++)
	{
		printw(" ");
		for (int x = 0; x < size; x++)
		{
			num = n->board[y * size + x];
			if (num == 0)
				printw("[%2c]", ' ');
			else if (num == complete_board[y * size + x]) //green
			{
				right_pos_count++;
				printw("[");
				attrset(COLOR_PAIR(CURSES_GREEN_BLACK));
				printw("%2d", num);
				attrset(COLOR_PAIR(CURSES_WHITE_BLACK));
				printw("]");
			}
			else
			{
				printw("[");
				attrset(COLOR_PAIR(CURSES_RED_BLACK));
				printw("%2d", num);
				attrset(COLOR_PAIR(CURSES_WHITE_BLACK));
				printw("]");
			}
		}
		printw("\n");
	}
	if (right_pos_count == limit - 1)
	{
		attrset(COLOR_PAIR(CURSES_GREEN_BLACK));
		printw("\n ===== Congratulations!! =====\n", num);
		attrset(COLOR_PAIR(CURSES_WHITE_BLACK));
	}

	printw("\n === === COMMANDS === ===\n\n");
	printw("  W | key up    : UP\n");
	printw("  S | key down  : DOWN\n");
	printw("  D | key right : RIGHT\n");
	printw("  A | key left  : LEFT\n");
	printw("  Q             : exit\n");
	printw("  R             : restart\n");
	printw("  U             : undo\n");


}

void	PlaySlidePuzzle::add_step(Node *n)
{
	history.push_back(*n);
}

void	PlaySlidePuzzle::init()
{
	limit = current_node.board.size(); 
	size = sqrt(limit);
	history.push_back(current_node);
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
		add_step(&current_node);
	}
}

void	PlaySlidePuzzle::start(Node node)
{
	current_node = node;
	start_node = node;
	index = 0;

	init();
	initscr();
	start_color();
	init_pair(CURSES_BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);		/* #1: fg=blue,    bg=black */
	init_pair(CURSES_RED_BLACK, COLOR_RED, COLOR_BLACK);		/* #2: fg=red,     bg=black */
	init_pair(CURSES_MAGENTA_BLACK, COLOR_MAGENTA, COLOR_BLACK);/* #3: fg=mazenta, bg=black */
	init_pair(CURSES_GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);	/* #4: fg=green,   bg=black */
	init_pair(CURSES_CYAN_BLACK, COLOR_CYAN, COLOR_BLACK);		/* #5: fg=cyan,    bg=black */
	init_pair(CURSES_YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);	/* #6: fg=yellow,  bg=black */
	init_pair(CURSES_WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);	/* #7: fg=white,   bg=black */

	int		c;

	display_node(&current_node);
	while (1)
	{
		if ((c = getch()) != ERR)	
		{
			if (c == 'q')
				break;
			if (c == 'w' || c == 'k')
				move_step(0, -1, "UP");
			if (c == 'a' || c == 'h')
				move_step(-1, 0, "LEFT");
			if (c == 'd' || c == 'l')
				move_step(1, 0, "RIGHT");
			if (c == 's' || c == 'j')
				move_step(0, 1, "DOWN");
			if (c == 'r')
			{
				current_node = start_node;
				history.clear();
				history.push_back(current_node);
			}
			if (c == 'u')
			{
				if (history.size() >= 2)
					history.pop_back();
				current_node = history.back();
			}
			clear();
			display_node(&current_node);

			if (c == 27)
			{
				c = getch();
				clear();
				display_node(&current_node);
				if (c == 91)
				{
					c = getch();
					if (c == 'A')
						move_step(0, -1, "UP");
					if (c == 'D')
						move_step(-1, 0, "LEFT");
					if (c == 'C')
						move_step(1, 0, "RIGHT");
					if (c == 'B')
						move_step(0, 1, "DOWN");

					clear();
					display_node(&current_node);
				}
			}
		}
	}
	display_node(&current_node);
	node.show();

	endwin();
	exit(0);
}
