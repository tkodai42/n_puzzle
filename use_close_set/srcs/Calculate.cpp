/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseArgv.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:28:07 by tkodai            #+#    #+#             */
/*   Updated: 2023/02/06 16:53:27 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Calculate.hpp"

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
 *  -c		calculation
 *
 *	-p		can play n_puzzle!!!
 */

void		show_xy(int xy[4])
{
	std::cout << "[x1: " << xy[0] << "] ";
	std::cout << "[y1: " << xy[1] << "] ";
	std::cout << "[x2: " << xy[2] << "] ";
	std::cout << "[y2: " << xy[3] << "] ";
	std::cout << std::endl;
}

void		init_num(int xy[4])
{
	for (int i = 0; i < 4; i++)
		xy[i] = 0;
}


void		Calculate::start()
{
	int		P1X	= 0;
	int		P1Y	= 1;
	int		P2X = 2;
	int		P2Y = 3;

	int		xy[4] = {0};
//	int		original_xy[4];

	show_xy(xy);
/*	std::cout << ">> [x1]" << std::endl;
	std::cin >> xy[P1X];
	show_xy(xy);

	std::cout << ">> [y1]" << std::endl;
	std::cin >> xy[P1Y];
*/

	std::cout << std::endl;
	show_xy(xy);

	std::cout << ">> [x2]" << std::endl;
	std::cin >> xy[P2X];
	show_xy(xy);

	std::cout << ">> [x2]" << std::endl;
	std::cin >> xy[P2Y];
	show_xy(xy);
	// set 


	// MD
	std::cout << "\n[ manhattan distance ]\n : abs(x1 - x2) + abs(y1 - y2)" << std::endl;
	std::cout << " >> " << abs(xy[P1X] - xy[P2X]) + abs(xy[P1Y] - xy[P2Y]) << std::endl;

	// MD2
	std::cout << "\n[ manhattan distance 2 ]\n : abs(x1 - x2) * abs(x1 - x2) + abs(y1 - y2) * abs(y1 - y2)" << std::endl;
	std::cout << " >> "
		<< abs(xy[P1X]-xy[P2X]) * abs(xy[P1X]-xy[P2X]) + abs(xy[P1Y]-xy[P2Y]) * abs(xy[P1Y]-xy[P2Y]) << std::endl;

	// ED
	std::cout << "\n[ euclidean distance ]\n : sqrt( abs(x1-x2) * abs(x1-x2) + abs(y1-y2) * abs(y1-y2) )" << std::endl;
	std::cout << " >> "
		<< sqrt(abs(xy[P1X]-xy[P2X]) * abs(xy[P1X]-xy[P2X]) + abs(xy[P1Y]-xy[P2Y]) * abs(xy[P1Y]-xy[P2Y])) << std::endl;

}
