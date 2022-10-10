#include "Taquin.hpp"

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
	int					limit = this->size * this->size;
	std::vector<int>	check;
	int					x = 0;
	int					y = 0;
	int					move_x = 1;
	int					move_y = 0;
	int					tmp_x;
	int					tmp_y;
	int					next_flag;
	
	this->goal_board.assign(limit, 0);
	check.assign(limit, 0);

	for (int i = 1; i < limit; i++)
	{
		check[y * this->size + x] = 1;
		goal_board[y * this->size + x] = i;

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
		}
		x = tmp_x;
		y = tmp_y;
	}
}

void	Taquin::expansion()
{
	
}


void	Taquin::start(std::vector<int> _board, int _size)
{
	std::cout << "\n--- Taquin::start ---\n" << std::endl;
	this->size = _size;
	generate_goal_board();
	this->zh.init(_size * _size, _size * _size); //hash

	Node tmp_node;

	tmp_node.board = _board;
	tmp_node.hash = this->zh.generate_hash(_board);
	tmp_node.n = 0;

	open_queue.push(tmp_node);
	while (!open_queue.empty())
	{
		tmp_node = open_queue.top(); //get highest
		open_queue.pop();
		this->current = &tmp_node;
		
		tmp_node.show();
		
		expansion();
	}
}
