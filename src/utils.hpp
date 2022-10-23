/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:58:47 by tkodai            #+#    #+#             */
/*   Updated: 2022/10/23 21:58:48 by tkodai           ###   ########.fr       */
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

#define	NOMAL_STATE	0
#define ERROR_OPEN	2

#define	SEARCH_MANHATTAN_DISTANCE			0
#define	SEARCH_IMPROVED_MANHATTAN_DISTANCE	1
#define	SEARCH_CORRECT_NUMBER_OF_PIECES		2
#define	SEARCH_BOGO							3

#define	SEARCH_UNIFORM_COST					4
#define	SEARCH_GREEDY						5

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

