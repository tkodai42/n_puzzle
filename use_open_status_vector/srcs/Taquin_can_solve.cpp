#include "Taquin.hpp"

void	Taquin::can_solve(std::vector<int> _board, int size)
{
	int					swap_count = 0;
	int					tag_index;
	int					num;
	std::vector<int>	_check_board;

	_check_board = _board;
	//search
	for (unsigned int i = 0; i < _board.size(); i++)
	{
		num = goal_board[i];
		if (_board[i] != num)
		{
			//search target
			for (tag_index = i; (unsigned int)tag_index < _board.size(); tag_index++)
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
	//0
	int	_b_0_x;
	int _b_0_y;
	int _g_0_x;
	int _g_0_y;

	for (unsigned int i = 0; i < _board.size(); i++)
	{
		if (_check_board[i] == 0)
		{
			_b_0_y = i / size;
			_b_0_x = i % size;
		}
		if (goal_board[i] == 0)
		{
			_g_0_y = i / size;
			_g_0_x = i % size;
		}
	}
	int	dist = abs(_b_0_x - _g_0_x) + abs(_b_0_y - _g_0_y);
		dist = abs(dist);
	if ((swap_count & (1 << 0)) != (dist & (1 << 0)))
		throw Taquin::UnsolvableException();

	//if (swap_count & (1 << 0))
	//	throw Taquin::UnsolvableException();
}
