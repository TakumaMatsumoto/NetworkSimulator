#include "stdafx.h"
using namespace std;
static const unsigned int DEFAULT_NUMBER_OF_TRIALS = 1000;

int main(int argc, char* argv[]) {
	int opt;
	opterr = 0;
	unsigned int number_of_trials = DEFAULT_NUMBER_OF_TRIALS;
	std::string sim_dll_filename;
	std::vector<std::string> result_dlls_filename;
	std::string param_table_filename;
	while ((opt = getopt(argc, argv, "c:i:r:")) != -1)
	{
		switch (opt)
		{
		case 'c':
			sim_dll_filename = optarg;
			break;
		case 'i':
			param_table_filename = optarg;
			break;
		case 'r':
			number_of_trials = std::stoul(optarg);
			break;
		default:
			cout << "Usage: "
 				 << argv[0]
				 << "[-c arg]" 
				 << "[-i arg]"
				 << "[-r arg]"
				 << "arg1 ..." << endl;
			cout << "option:" << endl;
			cout << "-c: filename of simulation dll" << endl;
			cout << "-i: filename of csv parameter table" << endl;
			cout << "-r: number of trials" << endl;
			cout << "arg1...: filenames of result dll" << endl;
			return 0;
			break;
		}
	}

	for (size_t i = optind; i < argc; i++)
	{
		result_dlls_filename.push_back(argv[i]);
	}

	sim::Simulator(
		sim::Config(number_of_trials, sim_dll_filename, result_dlls_filename), 
		table::FileStorage(param_table_filename).load()).run();
	return 0;
}