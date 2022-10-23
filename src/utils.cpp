/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:57:54 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/23 21:57:56 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

int		g_debug = 1;
int		g_hueristics_type;

void	show_message(const char *message, int flag = 0)
{
	if (flag == DEBUG_ERROR)
	{
		std::cout << COUT_RED << "Error: " << message << COUT_END << std::endl;
		return ;
	}
	if (g_debug == 0)
		return ;
	if (flag == DEBUG_FUNCTION)
	{
		std::cout << COUT_GREEN << "[" << message << "]" << COUT_END << std::endl;
	}
	else if (flag == DEBUG_MESSAGE)
	{
		std::cout << COUT_GREEN << "> " << message << COUT_END << std::endl;
	}
	else
		std::cout <<  "--- " << message << " ---" << std::endl;
}
