/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:56:23 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/23 21:56:26 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"
#include "ReadFile.hpp"
#include "ParseData.hpp"
#include "Taquin.hpp"

int		g_heuristics_type;

void	n_puzzle(char *file_name)
{
	ReadFile	reader;
	ParseData	parser;
	Taquin		taquin;

	if (reader.start(file_name) != NOMAL_STATE)
		return ;
	if (parser.start(reader.data_string) != NOMAL_STATE)
		return ;	
	parser.show();
	taquin.start(parser.get_board(), parser.board_size);
}

int		main(int argc, char *argv[])
{
	std::cout << "--- n_puzzle ---" << std::endl;
	
	//check args
	g_heuristics_type = SEARCH_MANHATTAN_DISTANCE;
	if (argc != 2)
		return 0;
	n_puzzle(argv[1]);
}
