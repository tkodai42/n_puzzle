#include "Taquin.hpp"

void	Taquin::can_solve(std::vector<int> _board, int size)
{
	int					swap_count = 0;
	int					tag_index;
	int					num;
	std::vector<int>	_except_0_board;
	std::vector<int>	_except_0_goal_board;

	//set
	for (int i = 0; i < _board.size(); i++)
	{
		if (_board[i] != 0)
		{
			_except_0_board.push_back(_board[i]);
		}
		if (goal_board[i] != 0)
		{
			_except_0_goal_board.push_back(goal_board[i]);
		}
	}
	//search
	_board = _except_0_board;
	for (int i = 0; i < _board.size(); i++)
	{
		num = _except_0_goal_board[i];
		if (_board[i] != num)
		{
			//search target
			for (tag_index = i; tag_index < _board.size(); tag_index++)
			{
				if (num == _board[tag_index])
					break;
			}
			//swap
			_board[tag_index] = _board[i];
			_board[i] = num;
			swap_count++;
		}
	}
	if (swap_count & (1 << 0))
		throw Taquin::UnsolvableException();
}
