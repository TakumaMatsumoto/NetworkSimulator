#pragma once

namespace ns{
	class RelayNode{
		geo::Point<double> m_pos;
	public:
		RelayNode(const geo::Point<double>& pos) : m_pos(pos){

		}
	};
	class RelayNodes{
		std::vector<RelayNode> m_relay_nodes;
	public:
		RelayNodes(const std::vector<RelayNode>& relay_nodes) : m_relay_nodes(relay_nodes){

		}
	};
}