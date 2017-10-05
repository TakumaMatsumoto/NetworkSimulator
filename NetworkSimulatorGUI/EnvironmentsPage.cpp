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
	const ns::Config def = ns::Config();
	wxVector<wxVariant> data;
	data.push_back(wxVariant(std::to_string(def.m_area.getWidth())));
	data.push_back(wxVariant(std::to_string(def.m_area.getHeight())));
	data.push_back(wxVariant(std::to_string(def.m_simulation_period)));
	data.push_back(wxVariant(std::to_string(def.m_transmission_speed)));
	data.push_back(wxVariant(std::to_string(def.m_transmission_range)));
	data.push_back(wxVariant(std::to_string(def.m_message_size)));
	data.push_back(wxVariant(std::to_string(def.m_message_interval)));
	data.push_back(wxVariant(std::to_string(def.m_number_of_relay_nodes)));
	data.push_back(wxVariant(to_string(def.m_routing_protocol)));
	mp_list_ctrl->AppendItem(data);
}

void EnvironmentsPage::onDeleteItem(wxCommandEvent & event){

}

void EnvironmentsPage::onLoadItems(wxCommandEvent & event){

}

void EnvironmentsPage::onSaveItems(wxCommandEvent & event){

}

EnvironmentsPage::EnvironmentsList::EnvironmentsList(wxWindow* p_parent) :
wxDataViewListCtrl(p_parent, wxID_ANY){
	AppendTextColumn(wxT("フィールド横幅(m)"),		 wxDATAVIEW_CELL_EDITABLE);
	AppendTextColumn(wxT("フィールド縦幅(m)"),		 wxDATAVIEW_CELL_EDITABLE);
	AppendTextColumn(wxT("シミュレーション時間(s)"), wxDATAVIEW_CELL_EDITABLE);
	AppendTextColumn(wxT("通信速度(bps)"),			 wxDATAVIEW_CELL_EDITABLE);
	AppendTextColumn(wxT("通信可能範囲(m)"),		 wxDATAVIEW_CELL_EDITABLE);
	AppendTextColumn(wxT("メッセージ長(bit)"),		 wxDATAVIEW_CELL_EDITABLE);
	AppendTextColumn(wxT("メッセージ間隔(s)"),		 wxDATAVIEW_CELL_EDITABLE);
	AppendTextColumn(wxT("リレーノード数"),			 wxDATAVIEW_CELL_EDITABLE);
	AppendTextColumn(wxT("ルーティングプロトコル"),  wxDATAVIEW_CELL_EDITABLE);
}