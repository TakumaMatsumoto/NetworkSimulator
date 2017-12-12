#pragma once
#include <unordered_map>
#include <deque>
#include <fstream>
#include <string>
#include <sstream>

namespace std {
	template <>
	class hash<std::pair<std::string, std::string>> {
	public:
		size_t operator()(const std::pair<std::string, std::string>& x) const {
			return hash<std::string>()(x.first) ^ hash<std::string>()(x.second);
		}
	};
}

namespace table {
	class Cell {
	public:
		std::string m_value;
		Cell(const std::string& value) :
			m_value(value) {

		}
		Cell() : Cell("") {

		}
	};
	using RowHeader = std::string;
	using ColumnHeader = std::string;
	// first: row
	// second: column
	using Index = std::pair<RowHeader, ColumnHeader>;
	class Table {
	private:
		std::vector<RowHeader> m_row_headers;
		std::vector<ColumnHeader> m_column_headers;
		std::unordered_map<Index, Cell> m_data;
		void insertRowHeader(const RowHeader& row) {
			if (std::find(
				m_row_headers.begin(),
				m_row_headers.end(),
				row) == m_row_headers.end()) {
				m_row_headers.push_back(row);
			}
		}
		void insertColumnHeader(const ColumnHeader& column) {
			if (std::find(
				m_column_headers.begin(),
				m_column_headers.end(),
				column) == m_column_headers.end()) {
				m_column_headers.push_back(column);
			}
		}
	public:
		std::vector<RowHeader> getRowHeaders() const {
			return m_row_headers;
		}
		std::vector<ColumnHeader> getColumnHeaders() const {
			return m_column_headers;
		}
		// row_headで指定した行を取得します
		// key:   カラム名
		// value: 値
		std::unordered_map<std::string, std::string> getRow(const std::string& row_head) const {
			std::unordered_map<std::string, std::string> ret;
			for (const auto& column_head : getColumnHeaders())
			{
				ret.insert(std::make_pair(column_head, this->cell(Index(row_head, column_head)).m_value));
			}
			return ret;
		}
		void insert(const Index& index, const Cell& cell) {
			// 高速化のために行・列のヘッダを保存
			insertRowHeader(index.first);
			insertColumnHeader(index.second);
			auto itr = m_data.find(index);
			if (itr != m_data.end()) {
				itr->second = cell;
				return;
			}
			m_data.insert(std::make_pair(index, cell));
		}
		// indexに保存されているセルを取得します
		inline Cell cell(const Index& index) const {
			return m_data.at(index);
		}
		std::string toCSVText() const {
			std::string ret = ",";
			// 一行目
			for (const auto& rheader : m_column_headers)
			{
				ret += rheader + ",";
			}
			ret.pop_back();
			ret += "\n";
			// 二行目以降
			for (const auto& lheader : m_row_headers)
			{
				ret += lheader + ",";
				for (const auto& rheader : m_column_headers)
				{
					const Index index = Index(RowHeader(lheader), ColumnHeader(rheader));
					ret += m_data.at(index).m_value + ",";
				}
				ret.pop_back();
				ret += "\n";
			}
			ret.pop_back();
			return ret;
		}
		static Table fromCSVText(
			const std::string& text,
			const bool header_exists) {
			const auto rows = [&]() {
				std::vector<std::string> ret;
				std::istringstream stream(text);
				stream.exceptions(std::ifstream::badbit);
				std::string row;
				while (std::getline(stream, row)) {
					ret.push_back(row);
				}
				return ret;
			}();
			const auto column_headers = [](const std::string& head) {
				std::vector<std::string> ret;
				std::istringstream stream(head);
				stream.exceptions(std::ifstream::badbit);
				std::string token;
				std::getline(stream, token, ',');
				while (std::getline(stream, token, ','))
				{
					ret.push_back(token);
				}
				return ret;
			}(rows[0]);
			Table ret;
			for (size_t i = 1, length = rows.size(); i < length; i++)
			{
				std::istringstream stream(rows[i]);
				stream.exceptions(std::ifstream::badbit);
				std::string row_header;
				std::getline(stream, row_header, ',');
				std::string token;
				int index = 0;
				while (std::getline(stream, token, ','))
				{
					ret.insert(
						Index(RowHeader(row_header), ColumnHeader(column_headers[index])),
						Cell(token));
					index++;
				}
			}
			return ret;
		}
	};
	class FileStorage {
	private:
		std::string m_file_name;
	public:
		FileStorage(const std::string& file_name)
			: m_file_name(file_name) {
		}
		table::Table load() const {
			std::ifstream ifs(m_file_name);
			ifs.exceptions(std::ifstream::badbit);
			const std::string str(
				(std::istreambuf_iterator<char>(ifs)),
				std::istreambuf_iterator<char>());
			return table::Table::fromCSVText(str, true);
		}
		void save(const table::Table& table) const {
			std::ofstream ofs(m_file_name);
			ofs.exceptions(std::ifstream::badbit);
			ofs << table.toCSVText();
			ofs.close();
		}
	};
}