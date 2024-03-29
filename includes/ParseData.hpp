#ifndef PARSEDATA_HPP
#define PARSEDATA_HPP

#include "utils.hpp"

class	ParseData
{
	public:
		std::string						raw_data;
		int								board_size;
		std::list<std::string>			board_list;
		std::vector<int> 				board;
		int								status;

	public:
		ParseData();
		int		start(std::string _data);
		void	pack_line();
		void	check_only_number();
		void	set_board(std::list<std::string>::iterator it);
		void	check_size();
		void	parse_line(const char *str);
		void	conflict_check();
		void	show();

		std::vector<int>	get_board();

		class	MapContainsNonAlphaException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return ("Error: ParseData: map contains non-alphabet");
				}
		};
		class	ParseDataException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return ("Error: ParseData: ");
				}
		};
		class	ParseDataNotSerialException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return ("Error: ParseData: not serial number");
				}
		};
};

#endif

