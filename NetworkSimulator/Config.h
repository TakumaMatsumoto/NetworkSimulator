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
		// �V�~�����[�V�����G���A[m^2]
		Area m_area;
		// �V�~�����[�V��������[s]
		int m_simulation_period;
		// �����[�m�[�h�̈ړ����x[m/s]
		int min, max;
		// �ʐM���x[bps]
		int m_transmission_speed;
		// �ʐM�\�͈�[m]
		double m_transmission_range;
		// ���b�Z�[�W�T�C�Y[bit]
		int m_message_size;
		// ���b�Z�[�W���M�Ԋu[s]
		int m_message_interval;
		// �����[�m�[�h��[��]
		int m_number_of_relay_nodes;
		// ���[�e�B���O�v���g�R��
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