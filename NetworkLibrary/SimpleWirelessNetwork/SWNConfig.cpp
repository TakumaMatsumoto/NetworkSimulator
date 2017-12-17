#include "SWNConfig.h"
using namespace sim::swn;

Config Config::createFromMap(const std::unordered_map<std::string, std::string>& umap) {
	Config ret;
	ret.m_simulation_period = std::stoul(umap.at("simulation_period"));
	ret.m_number_of_nodes	= std::stoul(umap.at("number_of_nodes"));
	ret.m_size_of_data		= std::stoul(umap.at("size_of_data"));
	ret.m_area_width		= std::stoul(umap.at("area_width"));
	ret.m_area_height		= std::stoul(umap.at("area_height"));
	return ret;
}
