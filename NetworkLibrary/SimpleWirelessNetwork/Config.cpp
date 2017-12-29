#include "SimpleWirelessNetwork\Config.h"
#include <string>
using namespace sim::swn;

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

Config Config::createFromMap(const std::unordered_map<std::string, std::string>& umap) {
	Config ret;
	// 地形に関する情報
	ret.m_area_width				 = std::stoul(umap.at("area_width"));
	ret.m_area_height				 = std::stoul(umap.at("area_height"));
	ret.m_number_of_sensor_nodes	 = std::stoul(umap.at("number_of_sensor_nodes"));
	{
		std::vector<std::string> result;
		split(umap.at("rails"), "|", result);
		for (const auto& s : result)
		{
			ret.m_rail_angles.push_back(std::stod(s));
		}
	}
	// ノードに関する情報
	ret.m_transmission_range.first	 = std::stod(umap.at("minimum_transmission_range"));
	ret.m_transmission_range.second  = std::stod(umap.at("maximum_transmission_range"));
	ret.m_message_size				 = static_cast<unsigned int>(std::stod(umap.at("message_size")));
	// エネルギーに関する情報
	ret.m_initial_energy			 = std::stod(umap.at("initial_energy"));
	ret.m_energy_consumption = EnergyConsumption(
		std::stod(umap.at("Emov")), 
		std::stod(umap.at("Eelec")),
		std::stod(umap.at("Eamp"))
	);
	// 障害物に関する情報
	ret.m_number_of_obstacles.first  = std::stoul(umap.at("minimum_number_of_obstacles"));
	ret.m_number_of_obstacles.second = std::stoul(umap.at("maximum_number_of_obstacles"));
	return ret;
}
