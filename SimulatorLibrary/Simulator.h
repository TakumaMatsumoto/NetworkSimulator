#pragma once
#include "Table.h"
#include "Config.h"
#include "IRunnable.h"

namespace sim
{
	class Simulator : IRunnable {
	private:
		Config m_conf;
		table::Table m_param_table;
	public:
		Simulator(const Config& conf, const table::Table& param_table) : m_conf(conf), m_param_table(param_table) {

		}
		void run() override;
		std::unordered_map<std::string, std::string> toMap() const override {

		}
	};
}