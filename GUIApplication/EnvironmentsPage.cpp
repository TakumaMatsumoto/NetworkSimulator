#include "EnvironmentsPage.h"
#include "Config.h"
enum class Command{
	ADD_ITEM = 0,
	DELETE_ITEM,
	LOAD_ITEMS,
	SAVE_ITEMS
};

enum class Columns{
	FIELD_WIDTH = 0,
	FIELD_HEIGHT,
	SIMULATION_PERIOD,
	TRANSMISSION_SPEED,
	TRANSMISSION_RANGE,
	MESSAGE_SIZE,
	MESSAGE_INTERVAL,
	NUMBER_OF_RELAY_NODES,
	ROUTING_PROTOCOL
};

std::string to_string(const ns::Config::RoutingProtocol& protocol){
	switch (protocol)
	{
	case ns::Config::RoutingProtocol::EPIDEMIC_ROUTING:
		return "Epidemic Routing";
		break;
	case ns::Config::RoutingProtocol::SPRAY_AND_WAIT:
		return "Spray and wait";
		break;
	default:
		break;
	}
	return "";
}

EnvironmentsPage::EnvironmentsPage(wxNotebook* p_parent) : wxPanel(p_parent, wxID_ANY){
	mp_list_ctrl = new EnvironmentsList(this);
	mp_add_item_button		= new wxButton(this, static_cast<int>(Command::ADD_ITEM),		"追加");
	mp_delete_item_button	= new wxButton(this, static_cast<int>(Command::DELETE_ITEM),	"削除");
	mp_load_items_button	= new wxButton(this, static_cast<int>(Command::LOAD_ITEMS),		"読み込み");
	mp_save_items_button	= new wxButton(this, static_cast<int>(Command::SAVE_ITEMS),		"名前を付けて保存");
	Connect(static_cast<int>(Command::ADD_ITEM), wxEVT_COMMAND_BUTTON_CLICKED
		, wxCommandEventHandler(EnvironmentsPage::onAddItem));
	Connect(static_cast<int>(Command::DELETE_ITEM), wxEVT_COMMAND_BUTTON_CLICKED
		, wxCommandEventHandler(EnvironmentsPage::onDeleteItem));
	Connect(static_cast<int>(Command::LOAD_ITEMS), wxEVT_COMMAND_BUTTON_CLICKED
		, wxCommandEventHandler(EnvironmentsPage::onLoadItems));
	Connect(static_cast<int>(Command::SAVE_ITEMS), wxEVT_COMMAND_BUTTON_CLICKED
		, wxCommandEventHandler(EnvironmentsPage::onSaveItems));

	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(mp_list_ctrl, 5, wxEXPAND);

	wxBoxSizer* bottomSizer = new wxBoxSizer(wxHORIZONTAL);
	bottomSizer->Add(mp_add_item_button, 1, wxEXPAND);
	bottomSizer->Add(mp_delete_item_button, 1, wxEXPAND);
	bottomSizer->Add(mp_load_items_button, 1, wxEXPAND);
	bottomSizer->Add(mp_save_items_button, 1, wxEXPAND);
	topSizer->Add(bottomSizer, 1, wxSHAPED);
	SetSizer(topSizer);
}

void EnvironmentsPage::onAddItem(wxCommandEvent& event){
	const int index = mp_list_ctrl->GetItemCount();
	mp_list_ctrl->InsertItem(index, wxString("0"));
	const ns::Config def = ns::Config();
	mp_list_ctrl->SetItem(index, static_cast<long>(Columns::FIELD_WIDTH),			std::to_string(def.m_area.getWidth()));
	mp_list_ctrl->SetItem(index, static_cast<long>(Columns::FIELD_HEIGHT),			std::to_string(def.m_area.getHeight()));
	mp_list_ctrl->SetItem(index, static_cast<long>(Columns::SIMULATION_PERIOD),		std::to_string(def.m_simulation_period));
	mp_list_ctrl->SetItem(index, static_cast<long>(Columns::TRANSMISSION_SPEED),	std::to_string(def.m_transmission_speed));
	mp_list_ctrl->SetItem(index, static_cast<long>(Columns::TRANSMISSION_RANGE),	std::to_string(def.m_transmission_range));
	mp_list_ctrl->SetItem(index, static_cast<long>(Columns::MESSAGE_SIZE),			std::to_string(def.m_message_size));
	mp_list_ctrl->SetItem(index, static_cast<long>(Columns::MESSAGE_INTERVAL),		std::to_string(def.m_message_interval));
	mp_list_ctrl->SetItem(index, static_cast<long>(Columns::NUMBER_OF_RELAY_NODES), std::to_string(def.m_number_of_relay_nodes));
	mp_list_ctrl->SetItem(index, static_cast<long>(Columns::ROUTING_PROTOCOL),		to_string(def.m_routing_protocol));
}

void EnvironmentsPage::onDeleteItem(wxCommandEvent & event){

}

void EnvironmentsPage::onLoadItems(wxCommandEvent & event){

}

void EnvironmentsPage::onSaveItems(wxCommandEvent & event){

}

EnvironmentsPage::EnvironmentsList::EnvironmentsList(wxWindow* p_parent) :
wxListCtrl(p_parent, wxID_ANY, wxDefaultPosition, p_parent->GetSize(), wxLC_REPORT | wxLC_VIRTUAL){
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
}

wxString EnvironmentsPage::EnvironmentsList::OnGetItemText(long item, long column) const{
	return GetItemText(item, column);
}