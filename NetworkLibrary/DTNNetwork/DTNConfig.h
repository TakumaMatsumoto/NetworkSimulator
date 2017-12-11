#pragma once
#include "Area.h"
#include "Table.h"
#include "Shelter.h"
#include "Sufferer.h"
#include "RelayNode.h"

namespace ns{
	class DTNConfig{
	public:
		DTNConfig(){
		}
		enum class RoutingProtocol{
			EPIDEMIC_ROUTING = 1,
			SPRAY_AND_WAIT = 2
		};
		// シミュレーションエリア[m^2]
		Area m_area = geo::Rectangle<double>(geo::Point<double>(0.0, 0.0), 0.0, 0.0);
		// シミュレーション時間[s]
		int m_simulation_period = 0;
		// リレーノードの最高移動速度[m/s]
		int m_max_move_speed = 0;
		// リレーノードの最低移動速度[m/s]
		int m_min_move_speed = 0;
		// 通信速度[bps]
		int m_transmission_speed = 0;
		// 通信可能範囲[m]
		double m_transmission_range = 0.0;
		// メッセージサイズ[bit]
		int m_message_size = 0;
		// メッセージ送信間隔[s]
		int m_message_interval = 0;
		// リレーノード数[個]
		int m_number_of_relay_nodes = 0;
		// ルーティングプロトコル
		RoutingProtocol m_routing_protocol = RoutingProtocol::EPIDEMIC_ROUTING;
		static DTNConfig createFromTable(const table::Table& tbl, const table::LineHeader& lhead);
	};
}