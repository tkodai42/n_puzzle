/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseArgv.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:28:07 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/27 00:04:59 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Option.hpp"

/*
 *	-h		help
 *	-f1		The Manhattan-distance | default	
 *	-f2		Improved Manhattan-distance
 *	-f3		Corrent number of pieces
 *	-f4		Search bogo => random
 *	-f5		Uniform Cost
 *	-f6		greedy search
 *	-f7		Original
 *
 *	-p		can play n_puzzle!!!
 */

void	Option::check_option_bit()
{
	std::cout << "   " << std::bitset<32>(this->option_bit) << std::endl;

	std::map<std::string, int>::iterator	it = option_bit_map.begin(); 
	std::map<std::string, int>::iterator	ite = option_bit_map.end();
	std::string on_off;

	for (; it != ite; it++)
	{
		if (this->option_bit & it->second)
		{
			on_off = "On: ";
		}
		else
			on_off = "- : ";
		std::cout << std::setw(4) << it->first << ": "
			<< on_off << option_name_map[it->second] << std::endl;
	}
}

void	Option::regist_map(std::string option, int bit, std::string option_name)
{
	this->option_bit_map.insert(std::make_pair(option, bit));
	this->option_name_map.insert(std::make_pair(bit, option_name));
}

void	Option::generate_bit_map()
{
	regist_map("h", BIT_HELP, "HELP");
	regist_map("f1", BIT_MANHATTAN_DISTANCE, "The Manhattan-distance");
	regist_map("f2", BIT_IMPROVED_MANHATTAN_DISTANCE, "Improved Manhattan-distance");
	regist_map("f3", BIT_CORRECT_NUMBER_OF_PIECES, "Corrent number of pieces");
	regist_map("f4", BIT_EUCLIDEAN_DISTANCE, "Euclidean-distance");
	regist_map("f5", BIT_BOGO, "Search bogo => ...random");
	regist_map("f6", BIT_UNIFORM_COST, "Uniform Cost");
	regist_map("f7", BIT_GREEDY, "greedy search");
	regist_map("f8", BIT_ORIGINAL, "Original");
	regist_map("f9", BIT_GREEDY_IMD, "greedy + Improved Manhattan-distance");
	regist_map("p", BIT_PLAY_GAME, "play n_puzzle!!!");
	regist_map("v", BIT_VISUALIZE, "visualize");
	regist_map("g", BIT_DEBUG, "debug");
}

void	Option::man()
{
	std::map<std::string, int>::iterator	it = option_bit_map.begin();
	std::map<std::string, int>::iterator	ite = option_bit_map.end();
	
	std::cout << "     " << "The options are as follows:\n" << std::endl;
	for (; it != ite; it++)
	{
		std::cout
			<< "     -" << std::left << std::setw(5) << it->first
			<< option_name_map[it->second] << std::endl;

		std::cout << std::endl;
	}
}

void	Option::put_manual()
{
	std::map<std::string, int>::iterator	it = option_bit_map.begin();
	std::map<std::string, int>::iterator	ite = option_bit_map.end();

	std::cout << "usege: n_puzzle ";
	for (; it != ite; it++)
		std::cout << "[-" << it->first << "] ";
	std::cout << "[file]" << std::endl; 
}

Option::Option()
{
	this->option_bit = 0;
	generate_bit_map();
}

int		Option::start(int argc, char *argv[])
{
	//set file
	this->file_index = argc - 1; //last argv
	
	std::map<std::string, int>::iterator	it; 
	std::map<std::string, int>::iterator	ite = option_bit_map.end();

	char 		*arg;
	std::string	check_arg1;
	std::string check_arg2;

	for (int i = 1; argv[i]; i++)
	{
		if (*argv[i] == '-')
		{
			arg = argv[i];
			arg++;
			while (*arg)
			{
				check_arg1 = *arg;
				it = option_bit_map.find(check_arg1);
				if (it == ite && *(arg + 1))
				{
					check_arg2 = *arg;
					check_arg2 += *(arg + 1);
					arg++;
					it = option_bit_map.find(check_arg2);
				}
				if (it == ite)
				{
					//std::cout << "Error: option " << argv[i] << std::endl;
					//exit(0);
				}
				else
				{
					this->option_bit |= it->second;
				}
				arg++;
			}
		}
		else if (i != file_index)
		{
			std::cout << "Error: option " << argv[i] << std::endl;
			exit(0);	
		}
	}
	if (option_bit & BIT_HELP)
	{
		man();
		return 42;
	}

	check_option_bit();

	if (option_bit == 0)
		option_bit |= BIT_MANHATTAN_DISTANCE;
	return NOMAL_STATE;
}
