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
	using LineHeader = std::string;
	using RowHeader = std::string;
	// first: line
	// second: row
	using Index = std::pair<LineHeader, RowHeader>;
	enum class TableType
	{
		ONE_DIMENSION = 0,
		TWO_DIMENSION = 1
	};
	class Table {
	private:
		std::vector<LineHeader> m_line_headers;
		std::vector<RowHeader> m_row_headers;
		std::unordered_map<Index, Cell> m_data;
		void insertLineHeader(const LineHeader& line) {
			if (std::find(
				m_line_headers.begin(),
				m_line_headers.end(),
				line) == m_line_headers.end()) {
				m_line_headers.push_back(line);
			}
		}
		void insertRowHeader(const RowHeader& row) {
			if (std::find(
				m_row_headers.begin(),
				m_row_headers.end(),
				row) == m_row_headers.end()) {
				m_row_headers.push_back(row);
			}
		}
	public:
		std::vector<LineHeader> getLineHeaders() const {
			return m_line_headers;
		}
		std::vector<RowHeader> getRowHeaders() const {
			return m_row_headers;
		}
		void insert(const Index& index, const Cell& cell) {
			// 高速化のために行・列のヘッダを保存
			insertLineHeader(index.first);
			insertRowHeader(index.second);
			auto itr = m_data.find(index);
			if (itr != m_data.end()) {
				itr->second = cell;
				return;
			}
			m_data.insert(std::make_pair(index, cell));
		}
		inline Cell cell(const Index& index) const {
			return m_data.at(index);
		}
		std::string toCSVText() const {
			std::string ret = ",";
			// 一行目
			for (const auto& rheader : m_row_headers)
			{
				ret += rheader + ",";
			}
			ret.pop_back();
			ret += "\n";
			// 二行目以降
			for (const auto& lheader : m_line_headers)
			{
				ret += lheader + ",";
				for (const auto& rheader : m_row_headers)
				{
					const Index index = Index(LineHeader(lheader), RowHeader(rheader));
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
			const bool header_exists,
			const TableType type) {
			const auto lines = [&]() {
				std::vector<std::string> ret;
				std::istringstream stream(text);
				std::string line;
				while (std::getline(stream, line)) {
					ret.push_back(line);
				}
				return ret;
			}();
			const auto row_headers = [](const std::string& head) {
				std::vector<std::string> ret;
				std::istringstream stream(head);
				std::string token;
				std::getline(stream, token, ',');
				while (std::getline(stream, token, ','))
				{
					ret.push_back(token);
				}
				return ret;
			}(lines[0]);
			Table ret;
			for (size_t i = 1, length = lines.size(); i < length; i++)
			{
				std::istringstream stream(lines[i]);
				std::string line_header;
				std::getline(stream, line_header, ',');
				std::string token;
				int index = 0;
				while (std::getline(stream, token, ','))
				{
					ret.insert(
						Index(LineHeader(line_header), RowHeader(row_headers[index])),
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
			const std::string str(
				(std::istreambuf_iterator<char>(ifs)),
				std::istreambuf_iterator<char>());
			return table::Table::fromCSVText(str, true, TableType::TWO_DIMENSION);
		}
		void save(const table::Table& table) const {
			std::ofstream ofs(m_file_name);
			ofs << table.toCSVText();
			ofs.close();
		}
	};
}