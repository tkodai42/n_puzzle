/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:56:23 by tkodai            #+#    #+#             */
/*   Updated: 2023/02/09 00:00:13 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"
#include "ReadFile.hpp"
#include "ParseData.hpp"
#include "Taquin.hpp"
#include "Option.hpp"

void	n_puzzle(int argc, char *argv[], time_t start_time)
{
	ReadFile	reader;
	ParseData	parser;
	Taquin		taquin;
	Option		parserArg;

	taquin.start_time = start_time;
	if (argc < 2)
	{
		parserArg.put_manual();	
		return ;
	}
	try
	{	
		parserArg.start(argc, argv);
		reader.start(argv[parserArg.file_index]);
		parser.start(reader.data_string);
		taquin.setting = &parserArg;
		taquin.input_data = reader.data_string;
		taquin.start(parser.get_board(), parser.board_size);
	}
	catch (std::exception &e)
	{
		if (e.what() == std::string("Calc"))
		{
			Calculate	calc;

			calc.start();
		}
		else
			std::cout << e.what() << std::endl;

	}
}

int		main(int argc, char *argv[])
{
	time_t	start_time = clock();

	n_puzzle(argc, argv, start_time);
}
