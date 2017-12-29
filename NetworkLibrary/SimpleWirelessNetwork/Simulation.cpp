#include "Simulation.h"
#include "Table.h"
#include "Result.h"
#include "UIDCreator.h"
using namespace sim::swn;
#define NRAND() static_cast<double>(rand()) / RAND_MAX

Simulation::Object Simulation::createObject() {
	UIDCreator uid_creator;
	// 初期化処理
	std::vector<std::shared_ptr<SensorNode>> snodes;
	// センサノードを配置
	for (unsigned int i = 0; i < m_conf.m_number_of_sensor_nodes; i++)
	{
		const auto point = geo::Point<double>(
			m_conf.m_area_width * NRAND(),
			m_conf.m_area_height * NRAND());
		const auto battery = Battery(m_conf.m_initial_energy);
		snodes.push_back(std::make_shared<SensorNode>(uid_creator.get(), point, m_conf.selectTransmissionRange(NRAND()), battery, m_conf.m_energy_consumption));
	}
	// 基地局(ベースノード)を配置
	const auto base_node = std::make_shared<BaseNode>(uid_creator.get(), geo::Point<double>(0.0, 0.0), m_conf.selectTransmissionRange(NRAND()));
	// センサノードの配列を基地局に近い順にする
	const auto sort_func = [&](const std::shared_ptr<SensorNode>& lhs, const std::shared_ptr<SensorNode>& rhs) {
		return lhs->getPosition().distanceTo(base_node->getPosition()) < rhs->getPosition().distanceTo(base_node->getPosition());
	};
	std::sort(snodes.begin(), snodes.end(), sort_func);
	SensorNodes sensor_nodes(snodes);
	// マップ情報の設定
	const auto nodes = [&]() {
		auto ret = sensor_nodes.getNodes();
		ret.push_back(base_node);
		return ret;
	}();
	const auto p_gmap = std::make_shared<GeometryMap>(Message(m_conf.m_message_size), m_conf.getRails(uid_creator), nodes);
	base_node->equip(p_gmap);
	sensor_nodes.equip(p_gmap);

	return Object(sensor_nodes, base_node, p_gmap);
}

std::vector<std::weak_ptr<INode>> Simulation::Object::getNodes() const {
	auto ret = mp_sensor_nodes.getNodes();
	ret.push_back(mp_base_node);
	return ret;
}

std::unordered_map<std::string, std::string> Simulation::run() {
	auto obj = createObject();
	// 一つのノードが死ぬまでにかかるラウンド数を数える
	unsigned int round = 0;
	while (obj.mp_sensor_nodes.areAlive())
	{
		// 地図情報を更新する
		obj.mp_gmap->update();
		// 全センサノードがデータのセンシングを行う
		obj.mp_sensor_nodes.sensing();
		// 全センサノードがレールへ移動する
		obj.mp_sensor_nodes.moveToRail();
		// 全センサノードが送信先センサノードを探す
		obj.mp_sensor_nodes.searchReceiver();
		// 全センサノードが送信元センサノードを探す
		obj.mp_sensor_nodes.searchSender();
		// ベースノードが収集元のノードを探す
		obj.mp_base_node->searchSender();
		// 収集元のノードからメッセージを取得する(移動含)
		const auto p_msg = obj.mp_base_node->collectMessage();
		unsigned int size = p_msg->getSize();
		// 全センサノードが初期位置へ戻る
		obj.mp_sensor_nodes.returnToInitialPosition();
		round++;
	}
	return Result(round, 0, 0.0, 0.0).toMap();
}