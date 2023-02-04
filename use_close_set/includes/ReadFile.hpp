/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadFile.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:58:15 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/27 23:01:28 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

		class	ReadException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return ("Error: ReadFile: read");
				}
		};

		class	OpenException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return ("Error: ReadFile: open");
				}
		};
};

#endif

