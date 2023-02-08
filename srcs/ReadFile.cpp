/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:57:10 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/27 22:50:58 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadFile.hpp"

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
	read_file_data();
	return this->status;
}

void	ReadFile::open_file()
{
	this->fd = open(this->file_name.c_str(), O_RDWR);
	if (this->fd < 0)
		throw	ReadFile::OpenException();
		//this->status = ERROR_OPEN;
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
			throw	ReadFile::ReadException();
			//std::cout << "Error: ReadFile: read" << std::endl;
			//exit(1);
		}
		if (ret == 0)
			break;
		buf[ret] = 0;
		this->data_string += buf;
	}
}


