/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:56:23 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/25 17:04:08 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"
#include "ReadFile.hpp"
#include "ParseData.hpp"
#include "Taquin.hpp"
#include "Manual.hpp"
#include "ParseArgv.hpp"

int		g_heuristics_type;

void	n_puzzle(int argc, char *argv[])
{
	ReadFile	reader;
	ParseData	parser;
	Taquin		taquin;
	ParseArgv	parserArg;

	if (parserArg.start(argc, argv) != NOMAL_STATE)
		return ;
	if (reader.start(argv[parserArg.file_index]) != NOMAL_STATE)
		return ;
	if (parser.start(reader.data_string) != NOMAL_STATE)
		return ;	
	parser.show();
	taquin.setting = &parserArg;
	taquin.start(parser.get_board(), parser.board_size);
}

int		main(int argc, char *argv[])
{
	g_heuristics_type = SEARCH_MANHATTAN_DISTANCE;
	if (argc < 2)
	{
		Manual	m;

		m.put_option_error();
		return 0;
	}
	n_puzzle(argc, argv);
}
