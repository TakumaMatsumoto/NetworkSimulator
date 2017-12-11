#include <vector>
#pragma once
namespace sim {
	// シミュレーションの設定パラメータクラス
	class Config {
	public:
		// 試行回数
		const unsigned int m_number_of_trials;
		// 実行するシミュレーションのdllファイル名
		const std::string m_simulation_dll_filename;
		// 結果出力を担当するdllファイル名
		const std::vector<std::string> m_output_dlls_filename;
		// シミュレーション全体の設定
		// @param number_of_trials:シミュレーション試行回数
		// @param simulation_dll_filename:シミュレーション方法が定義されたdllファイル名
		// @param output_dlls_filenam:シミュレーション結果の出力方法について定義されたdllファイル名群
		Config(
			const unsigned int number_of_trials, 
			const std::string& simulation_dll_filename,
			const std::vector<std::string>& output_dlls_filename) : 
			m_number_of_trials(number_of_trials),
			m_simulation_dll_filename(simulation_dll_filename),
			m_output_dlls_filename(output_dlls_filename){
		}
	};
}