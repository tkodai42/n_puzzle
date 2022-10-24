/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseArgv.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:24:26 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/24 17:37:32 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEARGV_HPP
#define PARSEARGV_HPP

#include "utils.hpp"

class	ParseArgv
{
	public:
		int							file_index;
		int							option_bit;
		std::map<std::string, int>	option_bit_map; //<option, bit>
		std::map<int, std::string>	option_name_map;//<bit, option str>

	public:
		int		start(int argc, char *argv[]);

		void	check_option_bit();

		void	generate_bit_map();
		void	regist_map(std::string s, int b, std::string on);

		ParseArgv();
};

#endif
