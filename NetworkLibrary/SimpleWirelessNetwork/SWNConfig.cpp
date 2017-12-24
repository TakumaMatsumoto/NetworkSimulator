#include "SWNConfig.h"
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
	ret.m_area_width				= std::stoul(umap.at("area_width"));
	ret.m_area_height				= std::stoul(umap.at("area_height"));
	ret.m_number_of_sensor_nodes	= std::stoul(umap.at("number_of_sensor_nodes"));
	ret.m_transmission_range		= std::stoul(umap.at("transmission_range"));
	ret.m_message_size				= std::stoul(umap.at("message_size"));
	ret.m_initial_energy			= std::stoul(umap.at("initial_energy"));
	ret.m_consume_energy_for_communication_per_bit = std::stod(umap.at("Eelec"));
	ret.m_consume_energy_for_transmission_per_bit  = std::stod(umap.at("Emp"));
	std::vector<std::string> result;
	split(umap.at("rails"), "|", result);
	for (const auto& s : result)
	{
		ret.m_rail_angles.push_back(std::stod(s));
	}
	return ret;
}
