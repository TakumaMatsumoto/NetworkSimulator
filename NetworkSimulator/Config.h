#pragma once
#include "Area.h"
#include "Table.h"
#include "Shelter.h"
#include "Sufferer.h"
#include "RelayNode.h"

namespace ns{
	class Config{
	public:
		Config() : m_area(geo::Rectangle<double>(geo::Point<double>(0.0, 0.0), 0.0, 0.0)){}
		enum class RoutingProtocol{
			EPIDEMIC_ROUTING = 1,
			SPRAY_AND_WAIT = 2
		};
		// シミュレーションエリア[m^2]
		Area m_area;
		// シミュレーション時間[s]
		int m_simulation_period;
		// リレーノードの移動速度[m/s]
		int min, max;
		// 通信速度[bps]
		int m_transmission_speed;
		// 通信可能範囲[m]
		double m_transmission_range;
		// メッセージサイズ[bit]
		int m_message_size;
		// メッセージ送信間隔[s]
		int m_message_interval;
		// リレーノード数[個]
		int m_number_of_relay_nodes;
		// ルーティングプロトコル
		RoutingProtocol m_routing_protocol;
		static Config createFromTable(const table::Table& tbl, const table::LineHeader& lhead);
	};
	class Configs{
		std::vector<Config> m_configs;
	public:
		Configs(const std::vector<Config>& configs) : m_configs(configs){}
		void add(const Config& conf){
			m_configs.push_back(conf);
		}
		std::vector<Config> get() const{
			return m_configs;
		}
		static Configs createFromTable(const table::Table& tbl);
	};
}