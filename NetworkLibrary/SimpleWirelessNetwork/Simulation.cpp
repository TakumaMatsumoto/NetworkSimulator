#include "Simulation.h"
#include "Table.h"
#include "Result.h"
#include "Node.h"
using namespace sim::swn;
#define NRAND() static_cast<double>(rand()) / INT_MAX

std::unordered_map<std::string, std::string> Simulation::run() {
	// 初期化処理
	SensorNodes sensor_nodes;
	// センサノードを配置
	for (unsigned int i = 0; i < m_conf.m_number_of_sensor_nodes; i++)
	{
		const auto point = geo::Point<double>(
			m_conf.m_area_width * NRAND(),
			m_conf.m_area_height * NRAND());
		const auto battery = Battery(m_conf.m_initial_energy);
		const auto antenner = Antenner(m_conf.m_consume_energy_for_communication_per_bit, m_conf.m_consume_energy_for_transmission_per_bit);
		sensor_nodes.add(std::make_shared<SensorNode>(point, m_conf.m_transmission_range, battery, antenner));
	}
	BaseNode base_node(geo::Point<double>(0.0, 0.0));
	// シミュレーションの空間情報
	const auto space = Space(Message(m_conf.m_message_size));
	// 一つのノードが死ぬまでにかかるラウンド数を数える
	unsigned int round = 0;
	while (sensor_nodes.areAlive())
	{
		// 全センサノードがデータのセンシングを行う
		sensor_nodes.sensing(space);
		// 全センサノードが送信先センサノードを探す(移動含)
		sensor_nodes.searchReceiver(sensor_nodes.getNodes());
		// ベースノードが収集元のノードを探す
		base_node.searchSender(sensor_nodes.getNodes());
		// 収集元のノードからメッセージを取得する
		base_node.collectMessage();
		round++;
	}
	return Result(round, 0.0, 0.0, 0.0).toMap();
}