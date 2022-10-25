/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:57:16 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/25 14:28:33 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Taquin.hpp"

void	Taquin::move_empty(int mx, int my)
{
	int			empty_pos = this->current->empty_y * size + this->current->empty_x;
	int			target_pos = (this->current->empty_y + my) * size + (this->current->empty_x + mx);
	int			target_num = current->board[target_pos];
	long long 	new_hash = 0;
	
	//swap
	new_hash = zh.update_hash(current->hash, current->board, empty_pos, target_num); //update empty -> target
	new_hash = zh.update_hash(new_hash, current->board, target_pos, 0); //update target -> empty

	//check hash, exist?
	if (hash_map.count(new_hash) == 1)
	{
		int index = hash_map[new_hash];

		if (node_vec[index].n > this->current->n)
		{
			Node	new_node;

			new_node = node_vec[index];
			new_node.n = this->current->n;
			new_node.parent_id = this->current->parent_id;
			//new_node.isOpen = 1;
			
			this->evaluation(&new_node);
			
			node_vec[index] = new_node;
			isOpen_vec[index] = OPEN_NODE;
			open_pque.push(INT_PAIR(new_node.w, index));
		}
	}
	else
	{
		Node	new_node;

		new_node = *current;
		new_node.hash = new_hash;
		new_node.empty_x += mx;
		new_node.empty_y += my;
		new_node.board[empty_pos] = target_num; //swap
		new_node.board[target_pos] = 0; //space
		this->evaluation(&new_node);

		new_node.id = node_vec.size();
		node_vec.push_back(new_node); //submit node
		isOpen_vec.push_back(OPEN_NODE);
		open_pque.push(INT_PAIR(new_node.w, new_node.id)); // submit open queue
		hash_map.insert(HASH_PAIR(new_node.hash, new_node.id)); // submit hash

		if (new_node.h == 0)
		{
			std::cout << hash_map.size() << std::endl;
			std::cout << open_pque.size() << std::endl;
			std::cout << node_vec.size() << std::endl;
			show_board(new_node.board, &new_node);
			show_path(&new_node);
			exit(0);
		}
	}
}

void	Taquin::expansion()
{
	this->current->n++;
	this->current->parent_id = this->current->id;
	//move	
	if (current->empty_x != 0)			//LEFT
		move_empty(-1, 0);
	if (current->empty_x != size - 1)	//RIGHT
		move_empty(1, 0);
	if (current->empty_y != 0)			//UP
		move_empty(0, -1);
	if (current->empty_y != size - 1)	//DOWN
		move_empty(0, 1);
}

void	Taquin::start(std::vector<int> _board, int _size)
{
	Node tmp_node;

	node_vec.reserve(10000);
	isOpen_vec.reserve(10000);

	this->size = _size;
	generate_goal_board();
	this->zh.init(_size * _size, _size * _size); //hash

	this->current = &tmp_node;
	tmp_node.board = _board;
	tmp_node.hash = this->zh.generate_hash(_board);
	tmp_node.parent_id = -1;
	tmp_node.isOpen = 1;
	tmp_node.n = 0;
	tmp_node.id = 0;
	tmp_node.set_empty();
	this->evaluation(&tmp_node);

	if (tmp_node.h == 0)
	{
		std::cout << hash_map.size() << std::endl;
		std::cout << open_pque.size() << std::endl;
		std::cout << node_vec.size() << std::endl;
		show_board(tmp_node.board, &tmp_node);
		show_path(&tmp_node);
		exit(0);
	}

	node_vec.push_back(tmp_node);
	isOpen_vec.push_back(OPEN_NODE);
	hash_map.insert(HASH_PAIR(tmp_node.hash, tmp_node.id)); //0 is node's id
	open_pque.push(INT_PAIR(tmp_node.w, tmp_node.id));//0 is node's id

	INT_PAIR index;
	while (!open_pque.empty())
	{
		index = open_pque.top();
		open_pque.pop();
		if (isOpen_vec[index.second] == CLOSE_NODE)
		{
			continue;
		}
		isOpen_vec[index.second] = CLOSE_NODE;
		tmp_node = node_vec[index.second];
		this->current = &tmp_node;
		expansion();
	}

}
