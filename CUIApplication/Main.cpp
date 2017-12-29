#include "stdafx.h"
#include "MSW\Simulator.h"
#include "SimulatorLibrary\Simulator.h"
#include "MSW\Config.h"
#include <memory>
using namespace std;
static const unsigned int DEFAULT_NUMBER_OF_TRIALS = 1000;

int main(int argc, char* argv[]) {
	int opt;
	opterr = 0;
	unsigned int number_of_trials = DEFAULT_NUMBER_OF_TRIALS;
	std::string simulation_dll_filename;
	std::string observer_dll_filename;
	std::string param_table_filename = "param.csv";
	while ((opt = getopt(argc, argv, "i:o:r:")) != -1)
	{
		switch (opt)
		{
		case 'i':
			param_table_filename = optarg;
			break;
		case 'o':
			observer_dll_filename = optarg;
			break;
		case 'r':
			number_of_trials = std::stoul(optarg);
			break;
		default:
			cout << "Usage: "
 				 << argv[0]
				 << " [-i arg]"
				 << " [-o arg]"
				 << " [-r arg]"
				 << " arg" << endl;
			cout << "option:" << endl;
			cout << "-i: filename of parameter csv file (default:param.csv)" << endl;
			cout << "-o: filename of observer dll" << endl;
			cout << "-r: number of trials" << endl;
			cout << "arg: filename of simulation dll" << endl;
			return -1;
			break;
		}
	}

	if (argc == 1) {
		cout << "Usage: "
			<< argv[0]
			<< " [-i arg]"
			<< " [-o arg]"
			<< " [-r arg]"
			<< " arg" << endl;
		cout << "option:" << endl;
		cout << "-i: filename of parameter csv file (default:param.csv)" << endl;
		cout << "-o: filename of observer dll" << endl;
		cout << "-r: number of trials" << endl;
		cout << "arg: filename of simulation dll" << endl;
		return -1;
	}
	simulation_dll_filename = argv[optind];

	try {
		const auto sim_conf = sim::Config(number_of_trials, table::FileStorage(param_table_filename).load());
		const auto msw_sim_conf = sim::msw::Config(sim_conf, simulation_dll_filename, observer_dll_filename);
		return sim::msw::Simulator(msw_sim_conf).run();
	}
	catch (const std::exception& ex) {
		cout << ex.what() << endl;
	}
	return -1;
}