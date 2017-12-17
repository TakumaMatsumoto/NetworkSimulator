#include "SWNConfig.h"
using namespace sim::swn;

Config Config::createFromMap(const std::unordered_map<std::string, std::string>& umap) {
	Config ret;
	ret.m_area_width			= std::stoul(umap.at("area_width"));
	ret.m_area_height			= std::stoul(umap.at("area_height"));
	ret.m_number_of_nodes		= std::stoul(umap.at("number_of_nodes"));
	ret.m_transmission_range	= std::stoul(umap.at("transmission_range"));
	ret.m_message_size			= std::stoul(umap.at("message_size"));
	ret.m_initial_energy		= std::stoul(umap.at("initial_energy"));
	return ret;
}
