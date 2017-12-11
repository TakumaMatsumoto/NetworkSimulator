#include "stdafx.h"

int main(int argc, char* argv[]) {
	sim::Simulator(sim::Config(1000, "", { "" }), table::FileStorage("").load()).run();
	return 0;
}