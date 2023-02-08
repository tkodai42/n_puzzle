/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlaySlidePuzzle.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:53:15 by tkodai            #+#    #+#             */
/*   Updated: 2022/12/11 18:29:45 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYSLIDEPUZZLE_HPP
#define PLAYSLIDEPUZZLE_HPP

#include "Node.hpp"
#include "utils.hpp"

#define	MY_KEY_CODE		27
#define MY_KEY_UP		'A'
#define MY_KEY_DOWN		'B'
#define MY_KEY_RIGHT	'C'
#define MY_KEY_LEFT		'D'

class	PlaySlidePuzzle
{
	public:
		std::list<Node>		history;
		std::vector<int>	complete_board;
		int					size;
		int					limit;
		int					index;
		Node				current_node;
		Node				start_node;

	public:
		void	start(Node node);
		void	display_node(Node *node);
		void	init();
		void	add_step(Node *n);
		void	move_step(int x, int y, std::string op);
		int		can_move(int x, int y, std::vector<int> b);
		void	move_empty(int x, int y);
};

#endif
