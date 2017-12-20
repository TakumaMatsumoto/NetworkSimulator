#include "Simulation.h"
#include "Table.h"
#include "Result.h"
#include "Node.h"
using namespace sim::swn;
#define NRAND() static_cast<double>(rand()) / INT_MAX

std::unordered_map<std::string, std::string> Simulation::run() {
	// ����������
	SensorNodes sensor_nodes;
	// �Z���T�m�[�h��z�u
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
	// �V�~�����[�V�����̋�ԏ��
	const auto space = Space(Message(m_conf.m_message_size));
	// ��̃m�[�h�����ʂ܂łɂ����郉�E���h���𐔂���
	unsigned int round = 0;
	while (sensor_nodes.areAlive())
	{
		// �S�Z���T�m�[�h���f�[�^�̃Z���V���O���s��
		sensor_nodes.sensing(space);
		// �S�Z���T�m�[�h�����M��Z���T�m�[�h��T��(�ړ���)
		sensor_nodes.searchReceiver(sensor_nodes.getNodes());
		// �x�[�X�m�[�h�����W���̃m�[�h��T��
		base_node.searchSender(sensor_nodes.getNodes());
		// ���W���̃m�[�h���烁�b�Z�[�W���擾����
		base_node.collectMessage();
		round++;
	}
	return Result(round, 0.0, 0.0, 0.0).toMap();
}