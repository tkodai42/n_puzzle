/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:58:47 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/25 17:09:00 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <iomanip>
#include <string>
#include <chrono>

#define	NOMAL_STATE	0
#define ERROR_OPEN	2

#define	SEARCH_MANHATTAN_DISTANCE			0
#define	SEARCH_IMPROVED_MANHATTAN_DISTANCE	1
#define	SEARCH_CORRECT_NUMBER_OF_PIECES		2
#define	SEARCH_BOGO							3

#define	SEARCH_UNIFORM_COST					4
#define	SEARCH_GREEDY						5
#define	SEARCH_ORIGINAL						6

#define	TMP_PLAY_GAME						10
#define TMP_HELP							11

#define	BIT_MANHATTAN_DISTANCE				(1<<SEARCH_MANHATTAN_DISTANCE)	
#define	BIT_IMPROVED_MANHATTAN_DISTANCE		(1<<SEARCH_IMPROVED_MANHATTAN_DISTANCE)
#define	BIT_CORRECT_NUMBER_OF_PIECES		(1<<SEARCH_CORRECT_NUMBER_OF_PIECES)
#define	BIT_BOGO							(1<<SEARCH_BOGO)
#define	BIT_UNIFORM_COST					(1<<SEARCH_UNIFORM_COST)
#define	BIT_GREEDY							(1<<SEARCH_GREEDY)
#define	BIT_ORIGINAL						(1<<SEARCH_ORIGINAL)
#define BIT_PLAY_GAME						(1<<TMP_PLAY_GAME)
#define BIT_HELP							(1<<TMP_HELP)

extern int g_debug;
extern int g_hueristics_type;

#define	DEBUG_FUNCTION	0
#define DEBUG_MESSAGE	1
#define DEBUG_ERROR		2

#define COUT_RED	"\x1b[31m"
#define COUT_GREEN	"\x1b[32m"
#define COUT_END	"\x1b[m"

void	show_message(const char *message, int flag);

#endif

