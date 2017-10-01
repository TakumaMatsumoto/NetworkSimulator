#pragma once
#include "Area.h"
#include "Shelter.h"
#include "Sufferer.h"
#include "RelayNode.h"

namespace ns{
	class Config{
	public:
		Area m_area;
		Shelters m_shelters;
		Sufferers m_sufferers;
		RelayNodes m_relay_nodes;
	};
}