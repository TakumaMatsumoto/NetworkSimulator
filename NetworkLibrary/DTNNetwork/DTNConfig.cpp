#include "DTNConfig.h"
using namespace ns;

DTNConfig DTNConfig::createFromTable(const table::Table& tbl, const table::LineHeader& lhead){
	DTNConfig ret;
	ret.m_area					= geo::Rectangle<double>(
									/* left bottom */	geo::Point<double>(0, 0),
									/* width  */		std::stod(tbl.cell(table::Index(lhead, "area_width")).m_value),
									/* height */		std::stod(tbl.cell(table::Index(lhead, "area_height")).m_value));
	ret.m_simulation_period		= std::stoi(tbl.cell(table::Index(lhead, "simulation_period")).m_value);
	ret.m_transmission_speed	= std::stoi(tbl.cell(table::Index(lhead, "transmission_speed")).m_value);
	ret.m_transmission_range	= std::stod(tbl.cell(table::Index(lhead, "transmission_range")).m_value);
	ret.m_message_size			= std::stoi(tbl.cell(table::Index(lhead, "message_size")).m_value);
	ret.m_message_interval		= std::stoi(tbl.cell(table::Index(lhead, "message_interval")).m_value);
	ret.m_number_of_relay_nodes = std::stoi(tbl.cell(table::Index(lhead, "number_of_relay_nodes")).m_value);
	ret.m_routing_protocol		= static_cast<DTNConfig::RoutingProtocol>(std::stoi(tbl.cell(table::Index(lhead, "routing_protocol")).m_value));
	return ret;
}
