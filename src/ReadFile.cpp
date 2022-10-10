#include "ReadFile.hpp"

int		ReadFile::put_error()
{
	std::cout << "Error: " << ERROR_OPEN << std::endl;
	return this->status;
}

ReadFile::ReadFile()
{
	this->file_name = "";
	this->fd = -1;
	this->data_string = "";
	this->status = NOMAL_STATE;
}

int	ReadFile::start(std::string _name)
{
	this->file_name = _name;
	this->fd = -1;
	this->data_string = "";
	this->status = NOMAL_STATE;

	open_file();
	if (this->status != NOMAL_STATE)
	{
		put_error();
		return this->status;
	}
	read_file_data();
	return this->status;
}

void	ReadFile::open_file()
{
	this->fd = open(this->file_name.c_str(), O_RDWR);
	if (this->fd < 0)
		this->status = ERROR_OPEN;
}

void	ReadFile::read_file_data()
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;

	while (1)
	{
		ret = read(this->fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			std::cout << "Error: ReadFile: read" << std::endl;
			exit(1);
		}
		if (ret == 0)
			break;
		buf[ret] = 0;
		this->data_string += buf;
	}
}


