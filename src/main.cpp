/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:56:23 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/26 23:21:46 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"
#include "ReadFile.hpp"
#include "ParseData.hpp"
#include "Taquin.hpp"
#include "Option.hpp"

int		g_heuristics_type;

void	n_puzzle(int argc, char *argv[])
{
	ReadFile	reader;
	ParseData	parser;
	Taquin		taquin;
	Option		parserArg;

	if (argc < 2)
	{
		parserArg.put_manual();	
		return ;
	}
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
	n_puzzle(argc, argv);
}
