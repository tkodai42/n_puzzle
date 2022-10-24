/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseArgv.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:28:07 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/24 17:37:30 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseArgv.hpp"

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

void	ParseArgv::check_option_bit()
{
	std::cout << std::bitset<32>(this->option_bit) << std::endl;

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

void	ParseArgv::regist_map(std::string option, int bit, std::string option_name)
{
	this->option_bit_map.insert(std::make_pair(option, bit));
	this->option_name_map.insert(std::make_pair(bit, option_name));
}

void	ParseArgv::generate_bit_map()
{
	regist_map("-h", BIT_HELP, "HELP");
	regist_map("-f1", BIT_MANHATTAN_DISTANCE, "The Manhattan-distance");
	regist_map("-f2", BIT_IMPROVED_MANHATTAN_DISTANCE, "Improved Manhattan-distance");
	regist_map("-f3", BIT_CORRECT_NUMBER_OF_PIECES, "Corrent number of pieces");
	regist_map("-f4", BIT_BOGO, "Search bogo => ...random");
	regist_map("-f5", BIT_UNIFORM_COST, "Uniform Cost");
	regist_map("-f6", BIT_GREEDY, "greedy search");
	regist_map("-f7", BIT_ORIGINAL, "Original");
	regist_map("-p", BIT_PLAY_GAME, "play n_puzzle!!!");
}

ParseArgv::ParseArgv()
{
	this->option_bit = 0;
	generate_bit_map();
}

int		ParseArgv::start(int argc, char *argv[])
{
	//set file
	this->file_index = argc - 1; //last argv
	
	std::map<std::string, int>::iterator	it; 
	std::map<std::string, int>::iterator	ite = option_bit_map.end();

	for (int i = 1; i < file_index; i++)
	{
		it = option_bit_map.find(argv[i]);
		if (it == ite)
		{
			std::cout << "Error: option " << argv[i] << std::endl;
		}
		else
		{
			this->option_bit |= it->second;
		}
		check_option_bit();
	}


	return NOMAL_STATE;
}
