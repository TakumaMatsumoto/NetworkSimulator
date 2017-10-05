#pragma once
#include "Config.h"

class EnvironmentsList : public wxListCtrl{
	enum class Columns{
		FIELD_WIDTH = 0,
		FIELD_HEIGHT,
		SIMULATION_PERIOD,
		TRANSMISSION_SPEED,
		TRANSMISSION_RANGE,
		MESSAGE_SIZE,
		MESSAGE_INTERVAL,
		NUMBER_OF_RELAY_NODES,
		ROUTING_PROTOCOL
	};
	ns::Configs m_configs;
public:
	EnvironmentsList(wxWindow* p_parent);
	wxString OnGetItemText(long item, long column) const;
};