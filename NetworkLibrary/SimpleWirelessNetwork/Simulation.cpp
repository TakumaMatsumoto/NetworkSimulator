#include "Simulation.h"
#include "Table.h"
#include "Result.h"
#include "UIDCreator.h"
using namespace sim::swn;
#define NRAND() static_cast<double>(rand()) / RAND_MAX

Simulation::Object Simulation::createObject() {
	UIDCreator uid_creator;
	// ����������
	std::vector<std::shared_ptr<SensorNode>> snodes;
	// �Z���T�m�[�h��z�u
	for (unsigned int i = 0; i < m_conf.m_number_of_sensor_nodes; i++)
	{
		const auto point = geo::Point<double>(
			m_conf.m_area_width * NRAND(),
			m_conf.m_area_height * NRAND());
		const auto battery = Battery(m_conf.m_initial_energy);
		snodes.push_back(std::make_shared<SensorNode>(uid_creator.get(), point, m_conf.selectTransmissionRange(NRAND()), battery, m_conf.m_energy_consumption));
	}
	// ��n��(�x�[�X�m�[�h)��z�u
	const auto base_node = std::make_shared<BaseNode>(uid_creator.get(), geo::Point<double>(0.0, 0.0), m_conf.selectTransmissionRange(NRAND()));
	// �Z���T�m�[�h�̔z�����n�ǂɋ߂����ɂ���
	const auto sort_func = [&](const std::shared_ptr<SensorNode>& lhs, const std::shared_ptr<SensorNode>& rhs) {
		return lhs->getPosition().distanceTo(base_node->getPosition()) < rhs->getPosition().distanceTo(base_node->getPosition());
	};
	std::sort(snodes.begin(), snodes.end(), sort_func);
	SensorNodes sensor_nodes(snodes);
	// �}�b�v���̐ݒ�
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
	// ��̃m�[�h�����ʂ܂łɂ����郉�E���h���𐔂���
	unsigned int round = 0;
	while (obj.mp_sensor_nodes.areAlive())
	{
		// �n�}�����X�V����
		obj.mp_gmap->update();
		// �S�Z���T�m�[�h���f�[�^�̃Z���V���O���s��
		obj.mp_sensor_nodes.sensing();
		// �S�Z���T�m�[�h�����[���ֈړ�����
		obj.mp_sensor_nodes.moveToRail();
		// �S�Z���T�m�[�h�����M��Z���T�m�[�h��T��
		obj.mp_sensor_nodes.searchReceiver();
		// �S�Z���T�m�[�h�����M���Z���T�m�[�h��T��
		obj.mp_sensor_nodes.searchSender();
		// �x�[�X�m�[�h�����W���̃m�[�h��T��
		obj.mp_base_node->searchSender();
		// ���W���̃m�[�h���烁�b�Z�[�W���擾����(�ړ���)
		const auto p_msg = obj.mp_base_node->collectMessage();
		unsigned int size = p_msg->getSize();
		// �S�Z���T�m�[�h�������ʒu�֖߂�
		obj.mp_sensor_nodes.returnToInitialPosition();
		round++;
	}
	return Result(round, 0, 0.0, 0.0).toMap();
}