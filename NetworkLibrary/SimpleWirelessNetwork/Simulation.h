#pragma once
#include <unordered_map>
#include "SimulatorLibrary\ISimulation.h"
#include "SimpleWirelessNetwork\Config.h"
#include "Node.h"

namespace sim {
	namespace swn {
		class Simulation : public ISimulation {
			const swn::Config m_conf;
			class Object {
			public:
				SensorNodes mp_sensor_nodes;
				std::shared_ptr<BaseNode> mp_base_node;
				std::shared_ptr<GeometryMap> mp_gmap;
				Object(const SensorNodes& p_sensor_nodes, const std::shared_ptr<BaseNode>& p_base_node, const std::shared_ptr<GeometryMap>& p_gmap) :
					mp_sensor_nodes(p_sensor_nodes), mp_base_node(p_base_node), mp_gmap(p_gmap) {

				}
				std::vector<std::weak_ptr<INode>> getNodes() const;
			};
			// シミュレーションに必要なオブジェクトを生成する
			Object createObject();
		public:
			Simulation(const std::unordered_map<std::string, std::string>& param_map) 
				: m_conf(Config::createFromMap(param_map)) {

			}
			std::unordered_map<std::string, std::string> run() override;
		};
	}
}