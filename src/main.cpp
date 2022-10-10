#include "n_puzzle.hpp"
#include "ReadFile.hpp"
#include "ParseData.hpp"
#include "Taquin.hpp"

void	n_puzzle(char *file_name)
{
	ReadFile	reader;
	ParseData	parser;
	Taquin		taquin;

	if (reader.start(file_name) != NOMAL_STATE)
		return ;
	if (parser.start(reader.data_string) != NOMAL_STATE)
		return ;	
	parser.show();
	taquin.start(parser.get_board(), parser.board_size);
}

int		main(int argc, char *argv[])
{
	std::cout << "--- n_puzzle ---" << std::endl;
	
	if (argc != 2)
		return 0;
	n_puzzle(argv[1]);
}
