#ifndef READ_FD_HPP	 
#define READ_FD_HPP	 

#include "utils.hpp"
#define BUFFER_SIZE 1000

class	ReadFile
{
	public:
		std::string		data_string;
		int				fd;
		std::string		file_name;
		int				status;

	public:
		ReadFile();
	
		int				start(std::string _file_name);
		void			read_file_data();
		void			open_file();
		int				put_error();
};

#endif

