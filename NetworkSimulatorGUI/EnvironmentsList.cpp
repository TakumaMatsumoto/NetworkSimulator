#include "EnvironmentsList.h"
#define STR(var) #var

EnvironmentsList::EnvironmentsList(wxWindow* p_parent) : 
wxListCtrl(p_parent, wxID_ANY, wxDefaultPosition, p_parent->GetSize(), wxLC_REPORT | wxLC_VIRTUAL)
, m_configs({ ns::Config() }){
	InsertColumn(static_cast<long>(Columns::FIELD_WIDTH),			wxT("フィールド横幅(m)"));
	InsertColumn(static_cast<long>(Columns::FIELD_HEIGHT),			wxT("フィールド縦幅(m)"));
	InsertColumn(static_cast<long>(Columns::SIMULATION_PERIOD),		wxT("シミュレーション時間(s)"));
	InsertColumn(static_cast<long>(Columns::TRANSMISSION_SPEED),	wxT("通信速度(bps)"));
	InsertColumn(static_cast<long>(Columns::TRANSMISSION_RANGE),	wxT("通信可能範囲(m)"));
	InsertColumn(static_cast<long>(Columns::MESSAGE_SIZE),			wxT("メッセージ長(bit)"));
	InsertColumn(static_cast<long>(Columns::MESSAGE_INTERVAL),		wxT("メッセージ間隔(s)"));
	InsertColumn(static_cast<long>(Columns::NUMBER_OF_RELAY_NODES), wxT("リレーノード数"));
	InsertColumn(static_cast<long>(Columns::ROUTING_PROTOCOL),		wxT("ルーティングプロトコル"));
	for (int i = 0; i < GetColumnCount(); i++)
	{
		SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
	}
	const auto configs = m_configs.get();
	for (size_t i = 0, length = configs.size(); i < length; i++)
	{

	}
}

wxString EnvironmentsList::OnGetItemText(long item, long column) const{
	const auto conf = m_configs.get()[item];
	switch (column){
	case static_cast<long>(Columns::FIELD_WIDTH) :
		return wxString(std::to_string(conf.m_area.getWidth()));
		break;
	case static_cast<long>(Columns::FIELD_HEIGHT) :
		return wxString(std::to_string(conf.m_area.getHeight()));
		break;
	case static_cast<long>(Columns::SIMULATION_PERIOD) :
		return wxString(std::to_string(conf.m_simulation_period));
		break;
	case static_cast<long>(Columns::TRANSMISSION_SPEED) :
		return wxString(std::to_string(conf.m_transmission_speed));
		break;
	case static_cast<long>(Columns::TRANSMISSION_RANGE) :
		return wxString(std::to_string(conf.m_transmission_range));
		break;
	case static_cast<long>(Columns::MESSAGE_SIZE) :
		return wxString(std::to_string(conf.m_message_size));
		break;
	case static_cast<long>(Columns::MESSAGE_INTERVAL) :
		return wxString(std::to_string(conf.m_message_interval));
		break;
	case static_cast<long>(Columns::NUMBER_OF_RELAY_NODES) :
		return wxString(std::to_string(conf.m_number_of_relay_nodes));
		break;
	case static_cast<long>(Columns::ROUTING_PROTOCOL) :
		return wxString(STR(conf.m_routing_protocol));
		break;
	default:
		wxFAIL_MSG("Invalid column index in MyListCtrl::OnGetItemText");
	}
	return wxString("");
}