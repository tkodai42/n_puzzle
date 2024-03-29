/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:58:47 by tkodai            #+#    #+#             */
/*   Updated: 2023/02/09 03:09:36 by tkodai           ###   ########.fr       */
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
#include <set>
#include <iomanip>
#include <string>
#include <math.h>
#include <chrono>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define	NOMAL_STATE	0
#define ERROR_OPEN	2

#define	SEARCH_MANHATTAN_DISTANCE			0
#define	SEARCH_IMPROVED_MANHATTAN_DISTANCE	1
#define	SEARCH_CORRECT_NUMBER_OF_PIECES		2
#define	SEARCH_EUCLIDEAN_DISTANCE			4
#define	SEARCH_BOGO							5

#define	SEARCH_UNIFORM_COST					6
#define	SEARCH_GREEDY						7
#define	SEARCH_ORIGINAL						8


#define	TMP_PLAY_GAME						9
#define TMP_HELP							10
#define TMP_VISUALIZE						11
#define TMP_DEBUG							12

#define	SEARCH_GREEDY_IMD					13

#define TMP_CALCULATION						14
#define TMP_USE_OPEN_VEC					15
#define TMP_NOT_DISPLAY						16

#define	BIT_MANHATTAN_DISTANCE				(1<<SEARCH_MANHATTAN_DISTANCE)	
#define	BIT_IMPROVED_MANHATTAN_DISTANCE		(1<<SEARCH_IMPROVED_MANHATTAN_DISTANCE)
#define	BIT_CORRECT_NUMBER_OF_PIECES		(1<<SEARCH_CORRECT_NUMBER_OF_PIECES)
#define	BIT_EUCLIDEAN_DISTANCE				(1<<SEARCH_EUCLIDEAN_DISTANCE)
#define	BIT_BOGO							(1<<SEARCH_BOGO)
#define	BIT_UNIFORM_COST					(1<<SEARCH_UNIFORM_COST)
#define	BIT_GREEDY							(1<<SEARCH_GREEDY)
#define	BIT_GREEDY_IMD						(1<<SEARCH_GREEDY_IMD)
#define	BIT_ORIGINAL						(1<<SEARCH_ORIGINAL)
#define BIT_PLAY_GAME						(1<<TMP_PLAY_GAME)
#define BIT_HELP							(1<<TMP_HELP)
#define BIT_VISUALIZE						(1<<TMP_VISUALIZE)
#define BIT_DEBUG							(1<<TMP_DEBUG)
#define BIT_CALCULATION						(1<<TMP_CALCULATION)
#define BIT_USE_OPEN_VEC					(1<<TMP_USE_OPEN_VEC)
#define BIT_NOT_DISPLAY						(1<<TMP_NOT_DISPLAY)

extern int g_debug;

#define	DEBUG_FUNCTION	0
#define DEBUG_MESSAGE	1
#define DEBUG_ERROR		2

#define COUT_RED	"\x1b[31m"
#define COUT_GREEN	"\x1b[32m"
#define COUT_END	"\x1b[m"

/* curses */
#define CURSES_BLUE_BLACK		1
#define CURSES_RED_BLACK		2
#define CURSES_MAGENTA_BLACK	3
#define CURSES_GREEN_BLACK		4
#define CURSES_CYAN_BLACK		5
#define CURSES_YELLOW_BLACK		6
#define CURSES_WHITE_BLACK		7

void	show_message(const char *message, int flag);

#endif

