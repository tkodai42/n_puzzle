#ifndef ZOBRISTHASH_HPP
#define ZOBRISTHASH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <time.h>

class	ZobristHash
{
	private:
		int								board_len;
		int								hand_num;
		std::vector<long long>			zobrist_table;

	public:
		ZobristHash() {}

		~ZobristHash() {}
	
		unsigned long long xor128()
		{
    		static unsigned long x = 123456789, y = 362436069, z = 521288629, w = 88675123; 
    		unsigned long t = (x ^ (x << 11));

			x = y; y = z; z = w;
			return(w = (w ^ (w >> 19)) ^ (t ^ (t >> 8))); 
		} 
		// xorshift => http://www.jstatsoft.org/v08/i14/

		void	init(int board_len, int hand_num)
		{
			this->board_len = board_len;
			this->hand_num = hand_num;
			this->zobrist_table.resize(board_len * hand_num);

			//srand((time(NULL)));
			for (int y = 0; y < this->board_len; y++)
			{
				for (int x = 0; x < hand_num; x++)
				{
					//this->zobrist_table[y * board_len + x] = ((long long)rand() << 32) + rand();
					this->zobrist_table[y * board_len + x] = xor128();
				}
			}
		}

		long long	generate_hash(std::vector<int> &_board)
		{
			long long	hash = 0;

			for (int i = 0; i < this->board_len; i++)
				hash = (hash ^ zobrist_table[i * hand_num + _board[i]]);
			return hash;
		}

		long long	update_hash(long long hash, std::vector<int> &_board, int pos, int act)
		{
			hash = hash ^ zobrist_table[pos * hand_num + _board[pos]];
			hash = hash ^ zobrist_table[pos * hand_num + act];
			return hash;
		}
};

#endif

//#include "ZobristHash.hpp"

/*
int		main()
{
	ZobristHash zh;
	zh.init(3, 4);
	long long hash;

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

