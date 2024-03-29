/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseData.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:57:01 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/08 16:46:00 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseData.hpp"

ParseData::ParseData() {};

void	ParseData::show()
{
	std::cout << ">> ParseData::show" << std::endl;
	std::cout << " > raw data ---" << std::endl;
	std::cout << raw_data << std::endl;
	std::cout << " > board size: " << board_size << std::endl;
	std::cout << " > status: " << status << std::endl;
}

std::vector<int>	ParseData::get_board()
{
	return this->board;
}

void	ParseData::pack_line()
{
	std::string	buffer = "";
	std::string::iterator	it = this->raw_data.begin();
	std::string::iterator	ite = this->raw_data.end();
	int	comment_flag = 0;

	for (; it != ite; it++)
	{
		if (*it == '\n')
		{
			this->board_list.push_back(buffer);
			buffer = "";
			comment_flag = 0;
			continue ;
		}
		if (*it == '#')
			comment_flag = 1;
		if (comment_flag == 0)
			buffer += *it;
	}
	if (buffer.size())
	{
		this->board_list.push_back(buffer);
		buffer = "";
		comment_flag = 0;
	}
}

void	ParseData::check_only_number()
{
	std::list<std::string>::iterator	it = this->board_list.begin();
	std::list<std::string>::iterator	ite = this->board_list.end();

	for (; it != ite; it++)
	{
		for (unsigned long i = 0; i < it->length(); i++)
		{
			if (!((*it)[i] == ' ' || ('0' <= (*it)[i] && (*it)[i] <= '9'))) //!(0 || number)
			{
				throw ParseData::MapContainsNonAlphaException();
			}
		}
	}
}

static int	simple_atoi(const char *str)
{
	int		ret = 0;

	while (str && *str)
	{
		if (!('0' <= *str && *str <= '9'))
			return -1;
		ret = ret * 10 + *str - '0';
		str++;
	}
	return ret;
}

static int		positive_atoi(const char **str)
{
	int		ret = 0;
	const char *pos = *str;

	if (*pos < '0' || '9' < *pos)
		return -1;
	
	while (*pos)
	{
		if (*pos < '0' || '9' < *pos)
			break ;
		ret = ret * 10 + *pos - '0';
		pos++;
	}
	*str = pos;
	return ret;
}

void	ParseData::parse_line(const char *str)
{
	int		content_count = 0;
	int		num;

	while (*str)
	{
		while (*str && *str == ' ') //skip space
			str++;
		if (*str) //pack num
		{
			num = positive_atoi(&str);
			if (num < 0)
			{
				throw ParseData::ParseDataException();
			}
			this->board.push_back(num);
			content_count++;
		}
	}
	if (content_count != this->board_size)
		throw ParseData::ParseDataException();
}

void	ParseData::set_board(std::list<std::string>::iterator it)
{
	std::list<std::string>::iterator	ite = this->board_list.end();

	for (; it != ite; it++)
	{
		parse_line((*it).c_str());
	}
	if (this->board.size() != (unsigned long)this->board_size * this->board_size)
		throw ParseData::ParseDataException();
}

void	ParseData::check_size()
{
	std::list<std::string>::iterator	it = this->board_list.begin();
	std::list<std::string>::iterator	ite = this->board_list.end();
	const char							*ptr;
	int									ret;

	for (; it != ite; it++)
	{
		if (it->length() == 0)
			continue;
		ptr = (*it).c_str();
		ret = simple_atoi(ptr);
		this->board_size = ret;
		if (ret == -1)
			throw ParseData::ParseDataException();
		it++;
		break ;
	}
	set_board(it);

	if (this->board_size <= 1)
		throw ParseData::ParseDataException();

}

void	ParseData::conflict_check()
{	
	std::map<int, int>	checker;

	for (unsigned long i = 0; i < this->board.size(); i++)
	{
		std::pair<std::map<int, int>::iterator, bool> res = 
			checker.insert(std::make_pair(this->board[i], 1));
		if (res.second == false)
		{
			//std::cout << "Error: conflict number" << std::endl;
			throw ParseData::ParseDataException();
		}
	}

	std::map<int, int>::iterator ite = checker.end();
	std::map<int, int>::iterator it;

	for (unsigned long i = 0; i < this->board.size(); i++)
	{
		it = checker.find(i);
		if (it == ite)
			throw ParseData::ParseDataNotSerialException();
	}
}

int		ParseData::start(std::string _data)
{
	this->raw_data = _data;
	this->board_size = 0;
	this->status = NOMAL_STATE;

	pack_line();
	check_only_number();
	check_size();
	conflict_check();

	return 0;
}

