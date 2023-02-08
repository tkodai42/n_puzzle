/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Taquin.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:57:16 by tkodai            #+#    #+#             */
/*   Updated: 2023/02/09 00:58:51 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Taquin.hpp"

void	Taquin::move_empty(int mx, int my)
{
	//current->show();
	empty_pos = this->current->empty_y * size + this->current->empty_x;
	target_pos = (this->current->empty_y + my) * size + (this->current->empty_x + mx);
	target_num = current->board[target_pos];
	empty_xy = index_to_xy(empty_pos);
	target_xy = index_to_xy(target_pos);
	long long 	new_hash = 0;

	std::map<long long, int>::iterator it;
	std::map<long long, int>::iterator ite = hash_map.end();;

	//only_original
	if (setting->option_bit & BIT_ORIGINAL)
	{
		if (is_solved[target_num] == 1)
		{
			return ;
		}
	}
	
	//swap
	new_hash = zh.update_hash(current->hash, current->board, empty_pos, target_num); //update empty -> target
	new_hash = zh.update_hash(new_hash, current->board, target_pos, 0); //update target -> empty

	//check hash, exist?
	if ((it = hash_map.find(new_hash)) != ite)
	{
		int index = it->second;

		if (node_vec[index].n > this->current->n)
		{
			Node	new_node = *(this->current);
			
			this->evaluation(&new_node);
			
			node_vec[index] = new_node;
			
			/* CLOSE LIST */
			if (this->setting->option_bit & BIT_USE_OPEN_VEC)
				isOpen_vec[index] = OPEN_NODE;

			closed_set.erase(index);

			open_pque.push(INT_PAIR(new_node.w, index));
		}
	}
	else
	{
		Node	new_node = *current;

		new_node.hash = new_hash;
		new_node.empty_x += mx;
		new_node.empty_y += my;
		new_node.board[empty_pos] = target_num; //swap
		new_node.board[target_pos] = 0; //space

		this->evaluation(&new_node);

		new_node.id = node_vec.size();//latest node
		node_vec.push_back(new_node); //submit node

		/* CLOSE LIST */
		if (this->setting->option_bit & BIT_USE_OPEN_VEC)
			isOpen_vec.push_back(OPEN_NODE);//add open list

		
		/*** original ***/
		//if destroy set => w = INFFFF

		open_pque.push(INT_PAIR(new_node.w, new_node.id)); // submit open queue
		hash_map.insert(HASH_PAIR(new_node.hash, new_node.id)); // submit hash

		if (new_node.h == 0)
		{
			display_result(new_node);
		}
	}
}

void	Taquin::expansion()
{
	this->current->n++;
	this->current->parent_id = this->current->id;
	empty_pos = this->current->empty_y * size + this->current->empty_x;

	//move	
	update_step = 0;
	if (current->empty_x != 0)			//LEFT
	{
		move_empty(-1, 0);
	}
	if (update_step == 0 && current->empty_x != size - 1)	//RIGHT
	{
		move_empty(1, 0);
	}
	if (update_step == 0 && current->empty_y != 0)			//UP
	{
		move_empty(0, -1);
	}
	if (update_step == 0 && current->empty_y != size - 1)	//DOWN
	{
		move_empty(0, 1);
	}
}

void	Taquin::init(Node &tmp_node, std::vector<int> &_board, int _size)
{
	std::cout << "\n ====== INPUT ======" << std::endl;
	std::cout << input_data << std::endl;
	std::cout << " ====================" << std::endl;

	//this->start_time = clock();
	opened_nodes_num= 0;

	node_vec.reserve(1000000);
	/* CLOSE LIST */
	if (this->setting->option_bit & BIT_USE_OPEN_VEC)
		isOpen_vec.reserve(1000000);

	this->size = _size;
	this->limit = _size * _size;
	generate_goal_board();
	
	can_solve(_board, _size);
	//check can solve
	this->zh.init(limit, limit); //hash

	this->current = &tmp_node;
	tmp_node.board = _board;
	tmp_node.hash = this->zh.generate_hash(_board);
	tmp_node.parent_id = -1;
	tmp_node.n = 0;
	tmp_node.id = 0;
	tmp_node.set_empty();
	this->evaluation(&tmp_node);
}

void	Taquin::display_result(Node &node)
{
	this->end_time = clock();
	show_path(&node);

	std::cout << "heuristics      : " << get_adopted_heuristic() << std::endl;
	if (setting->option_bit & BIT_GREEDY)
	std::cout << "bonus           : " << setting->option_name_map[BIT_GREEDY] << std::endl;
	if (setting->option_bit & BIT_UNIFORM_COST)
	std::cout << "bonus           : " << setting->option_name_map[BIT_UNIFORM_COST] << std::endl;
	//std::cout << "open queue      : " << open_pque.size() << std::endl;
	std::cout << "expanded nodes  : " << opened_nodes_num << std::endl;
	std::cout << "nodes           : " << node_vec.size() << std::endl;
	std::cout << "step            : " << node.n << std::endl;
	std::cout << "time            : " << (double)(end_time - start_time) / 1000000 << std::endl;
	exit(0);
}

void	Taquin::start(std::vector<int> _board, int _size)
{
	Node tmp_node;

	init(tmp_node, _board, _size);

	node_vec.push_back(tmp_node);
	/* CLOSE LIST */
	if (this->setting->option_bit & BIT_USE_OPEN_VEC)
		isOpen_vec.push_back(OPEN_NODE);
	hash_map.insert(HASH_PAIR(tmp_node.hash, tmp_node.id)); //0 is node's id
	open_pque.push(INT_PAIR(tmp_node.w, tmp_node.id));//0 is node's id

	if (tmp_node.h == 0)
		display_result(tmp_node);

	if (this->setting->option_bit & BIT_PLAY_GAME)
	{
		psp.complete_board = this->goal_board;
		psp.start(tmp_node);
	}

	INT_PAIR index;
	while (!open_pque.empty())
	{
		index = open_pque.top();
		open_pque.pop();

		/* CLOSE LIST */
		if (this->setting->option_bit & BIT_USE_OPEN_VEC)
		{
			if (isOpen_vec[index.second] == CLOSE_NODE)
				continue;
		}
		else
		{
			if (closed_set.count(index.second) != 0)
				continue ;
		}
		opened_nodes_num++;

		/* CLOSE LIST */
		if (this->setting->option_bit & BIT_USE_OPEN_VEC)
			isOpen_vec[index.second] = CLOSE_NODE;
		else
			closed_set.insert(index.second);

		tmp_node = node_vec[index.second];
		this->current = &tmp_node;

		if (setting->option_bit & BIT_DEBUG)
		{
			std::cout << "expanded nodes  : " << opened_nodes_num << std::endl;
			std::cout << "nodes           : " << node_vec.size() << std::endl;
			show_color_board(this->current->board, this->current);
		}
		expansion();
	}

}
