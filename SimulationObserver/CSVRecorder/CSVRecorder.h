#pragma once
#include "ISimulationObserver.h"
#include "Table.h"
template <typename List>
void split(const std::string& s, const std::string& delim, List& result)
{
	result.clear();

	using string = std::string;
	string::size_type pos = 0;

	while (pos != string::npos)
	{
		string::size_type p = s.find(delim, pos);

		if (p == string::npos)
		{
			result.push_back(s.substr(pos));
			break;
		}
		else {
			result.push_back(s.substr(pos, p - pos));
		}

		pos = p + delim.size();
	}
}

namespace sim {
	namespace observer {
		class CSVRecorder : public ISimulationObserver {
		public:
			class Config {
			public:
				const bool m_log = false;
				const std::string m_filename;
				Config(const std::string& filename) : m_filename(filename) {
				}
				static Config createFromConfigFile() {
					const std::string fname = "config.txt";
					std::ifstream ifs(fname);
					std::string str;
					std::unordered_map<std::string, std::string> umap;
					while (getline(ifs, str))
					{
						std::vector<std::string> map;
						split(str, "=", map);
						umap.insert({ map[0], map[1] });
					}
					return Config(umap.at("filename"));
				}
			};
			CSVRecorder(const Config& conf) : m_conf(conf) {

			}
			// �V�~�����[�^�J�n���Ɏ��s�����֐�
			// @param conf: �V�~�����[�^�̐ݒ�
			virtual void onSimulatorBegin(const sim::Config& conf) override {

			}
			// �����̃V�~�����[�V�����ݒ艺�ł̃V�~�����[�V�������J�n����^�C�~���O�Ŏ��s�����֐�
			// @param param_name:	�V�~�����[�V�����ݒ�̖��O
			// @param param:		�V�~�����[�V�����ݒ�
			virtual void onSimulationsBegin(const std::string& param_name, const std::unordered_map<std::string, std::string>& param) override {

			}
			// �V�~�����[�V�������J�n���閈�Ɏ��s�����֐�
			// @param current_trial_number: ���݂̎��s��
			virtual void onSimulationBegin(const unsigned int current_trial_number) override {

			}
			// �V�~�����[�V�������I�����閈�Ɏ��s�����֐�
			// @param current_trial_number: ���݂̎��s��
			// @param result: �V�~�����[�V��������
			virtual void onSimulationEnd(const unsigned int current_trial_number, const std::unordered_map<std::string, std::string>& result) override {

			}
			// �����̃p�����[�^�����ł̃V�~�����[�V�������I������^�C�~���O�Ŏ��s�����֐�
			// @param param_name:	�V�~�����[�V�����ݒ�̖��O
			// @param results: ���s�񐔕��̃V�~�����[�V��������
			virtual void onSimulationsEnd(const std::string& param_name, const std::vector<std::unordered_map<std::string, std::string>>& results) override {
				const auto chead = table::ColumnHeader(param_name);
				const auto keys = [&results]() {
					std::vector<std::string> ret;
					for (const auto& map : results[0])
					{
						ret.push_back(map.first);
					}
					return ret;
				}();
				// �e�L�[�̒l���擾���ĕ��ϒl���Z�o����
				for (const auto& key : keys)
				{
					const auto rhead = table::RowHeader(key);
					double ave = 0.0;
					for (const auto& result : results)
					{
						ave += std::stod(result.at(key));
					}
					m_table.insert(
						table::Index(chead, rhead), 
						table::Cell(std::to_string(ave)));
				}
			}
			// �V�~�����[�^�I�����Ɏ��s�����֐�
			virtual void onSimulatorEnd() override {
				table::FileStorage(m_conf.m_filename).save(m_table);
			}
		private:
			const Config m_conf;
			table::Table m_table;
		};
	}
}