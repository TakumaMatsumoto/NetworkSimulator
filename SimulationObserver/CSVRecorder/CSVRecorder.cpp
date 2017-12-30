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

void CSVRecorder::onSimulationsEnd(const std::string& param_name, const sim::Results& results) {
	const auto chead = table::ColumnHeader(param_name);
	const auto keys = [&results]() {
		std::vector<std::string> ret;
		for (const auto& map : results[0])
		{
			ret.push_back(map.first);
		}
		return ret;
	}();
	// 各キーの値を取得して平均値を算出する
	for (const auto& key : keys)
	{
		const auto rhead = table::RowHeader(key);
		double ave = 0.0;
		for (const auto& result : results)
		{
			ave += std::stod(result.at(key));
		}
		m_table.insert(
			table::Index(chead, rhead),
			table::Cell(std::to_string(ave)));
	}
}
