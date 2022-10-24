/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manual.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:41:50 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/24 16:23:14 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MANUAL_HPP
#define	MANUAL_HPP

#include "utils.hpp"

class	Manual
{
	public:
		std::string		name;
		std::string		input_option;
		void			put_option_error();
		void			put_manual();
};

#endif
