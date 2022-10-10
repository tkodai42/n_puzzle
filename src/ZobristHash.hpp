#ifndef ZOBRISTHASH_HPP
#define ZOBRISTHASH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <time.h>

class	ZobristHash
{
	private:
		int							board_len;
		int							hand_num;
		std::vector<unsigned int>	zobrist_table;

	public:
		ZobristHash() {}

		~ZobristHash() {}
		
		void	init(int board_len, int hand_num)
		{
			this->board_len = board_len;
			this->hand_num = hand_num;
			this->zobrist_table.resize(board_len * hand_num);

			srand((time(NULL)));
			for (int y = 0; y < this->board_len; y++)
			{
				for (int x = 0; x < hand_num; x++)
				{
					this->zobrist_table[y * board_len + x] = rand();
				}
			}
		}

		unsigned int	generate_hash(std::vector<int> &_board)
		{
			unsigned int	hash = 0;

			for (int i = 0; i < this->board_len; i++)
				hash = (hash ^ zobrist_table[i * hand_num + _board[i]]);
			return hash;
		}

		unsigned int	update_hash(unsigned int hash,
									std::vector<int> &_board,
									int pos,
									int	act)
		{
			hash = hash ^ zobrist_table[pos * hand_num + _board[pos]];
			hash = hash ^ zobrist_table[pos * hand_num + act];
			return hash;
		}
};

/*
#include "ZobristHash.hpp"

int		main()
{
	ZobristHash zh;
	zh.init(3, 4);
	unsigned int hash;

	std::vector<int>	board1;

	board1.push_back(3);
	board1.push_back(1);
	board1.push_back(2);

	hash = zh.generate_hash(board1);
	std::cout << hash << std::endl;
	
	hash = zh.update_hash(hash, board1, 1, 2);
	std::cout << hash << std::endl;
	board1[1] = 2;
	hash = zh.update_hash(hash, board1, 1, 1);
	std::cout << hash << std::endl;
}
*/

#endif
