#include "CSVRecorder.h"
using namespace sim::observer;
template <typename List>
void split(const std::string& s, const std::string& delim, List& result)
{
	result.clear();

	using string = std::string;
	string::size_type pos = 0;

	while (pos != string::npos)
	{
		string::size_type p = s.find(delim, pos);

		if (p == string::npos)
		{
			result.push_back(s.substr(pos));
			break;
		}
		else {
			result.push_back(s.substr(pos, p - pos));
		}

		pos = p + delim.size();
	}
}

CSVRecorder::Config CSVRecorder::Config::createFromConfigFile() {
	const std::string fname = "config.txt";
	std::ifstream ifs(fname);
	std::string str;
	std::unordered_map<std::string, std::string> umap;
	while (getline(ifs, str))
	{
		std::vector<std::string> map;
		split(str, "=", map);
		umap.insert({ map[0], map[1] });
	}
	return Config(umap.at("filename"));
}

void CSVRecorder::updateTable(const sim::ResultNameTypePair& ntp, const std::string& param_name, const sim::Results& results) {
	if (ntp.second == "array") {
		table::Table& tbl = searchTableForColumn(ntp.first);
		std::vector<double> ave;
		// 最大配列数を取得する
		for (const Result result : results)
		{
			std::vector<std::string> values;
			split(result.at(ntp.first).second, ":", values);
			if (ave.size() < values.size()) ave.resize(values.size());
		}
		for (const Result result : results)
		{
			std::vector<std::string> values;
			split(result.at(ntp.first).second, ":", values);
			for (size_t i = 0, length = values.size(); i < length; i++)
			{
				ave[i] += std::stod(values[i]) / results.size();
			}
		}
		for (size_t i = 0, length = ave.size(); i < length; i++)
		{
			tbl.insert(
				table::Index(table::ColumnHeader("Sample" + std::to_string(i)), table::RowHeader(param_name)),
				table::Cell(std::to_string(ave[i])));
		}
	}
	if (ntp.second == "primitive") {
		double ave = 0.0;
		for (const Result result : results)
		{
			ave += std::stod(result.at(ntp.first).second) / results.size();
		}
		m_table_for_primitive_values.insert(
			table::Index(table::ColumnHeader(param_name), table::RowHeader(ntp.first)),
			table::Cell(std::to_string(ave)));
	}
}

void CSVRecorder::onSimulationsEnd(const std::string& param_name, const sim::Results& results) {
	const auto ntps = [&results]() {
		std::vector<sim::ResultNameTypePair> ret;
		for (const auto& map : results[0])
		{
			ret.push_back({ map.first, map.second.first });
		}
		return ret;
	}();
	// 各キーの値を取得して平均値を算出する
	for (const auto ntp : ntps)
	{
		updateTable(ntp,  param_name, results);
	}
}

void CSVRecorder::onSimulatorEnd() {
	for (const auto& table : m_tables_for_array_values)
	{
		table::FileStorage(table.first + "_" + m_conf.m_filename).save(table.second);
	}
	table::FileStorage(m_conf.m_filename).save(m_table_for_primitive_values);
}
