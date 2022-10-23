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
