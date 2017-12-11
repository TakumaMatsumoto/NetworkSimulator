#include "SWNConfig.h"
using namespace sim::swn;

Config Config::createFromTable(const table::RowHeader& row_header, const table::Table& tbl) {
	Config ret;
	ret.m_simulation_period = std::stoul(tbl.cell(table::Index(row_header, "simulation_period")).m_value);
	ret.m_number_of_nodes	= std::stoul(tbl.cell(table::Index(row_header, "number_of_nodes")).m_value);
	ret.m_size_of_data		= std::stoul(tbl.cell(table::Index(row_header, "size_of_data")).m_value);
	ret.m_area_width		= std::stoul(tbl.cell(table::Index(row_header, "area_width")).m_value);
	ret.m_area_height		= std::stoul(tbl.cell(table::Index(row_header, "area_height")).m_value);
	return ret;
}
