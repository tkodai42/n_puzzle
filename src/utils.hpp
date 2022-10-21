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

extern int g_debug;

#define	DEBUG_FUNCTION	0
#define DEBUG_MESSAGE	1
#define DEBUG_ERROR		2

#define COUT_RED	"\x1b[31m"
#define COUT_GREEN	"\x1b[32m"
#define COUT_END	"\x1b[m"

void	show_message(const char *message, int flag);

#endif

