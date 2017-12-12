#include "EnvironmentsPage.h"
#include "Config.h"
enum class Command{
	ADD_ITEM = 0,
	DELETE_ITEM,
	LOAD_ITEMS,
	SAVE_ITEMS
};

enum class ComponentID{
	LIST = 0
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
	mp_add_item_button		= new wxButton(this, static_cast<int>(Command::ADD_ITEM),		"�ǉ�");
	mp_delete_item_button	= new wxButton(this, static_cast<int>(Command::DELETE_ITEM),	"�폜");
	mp_load_items_button	= new wxButton(this, static_cast<int>(Command::LOAD_ITEMS),		"�ǂݍ���");
	mp_save_items_button	= new wxButton(this, static_cast<int>(Command::SAVE_ITEMS),		"���O��t���ĕۑ�");
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &EnvironmentsPage::onAddItem,	this, static_cast<int>(Command::ADD_ITEM));
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &EnvironmentsPage::onDeleteItem, this, static_cast<int>(Command::DELETE_ITEM));
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &EnvironmentsPage::onLoadItems,	this, static_cast<int>(Command::LOAD_ITEMS));
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &EnvironmentsPage::onSaveItems,	this, static_cast<int>(Command::SAVE_ITEMS));

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
wxDataViewListCtrl(
	p_parent, static_cast<int>(ComponentID::LIST), 
	wxDefaultPosition, wxDefaultSize, 
	wxDV_HORIZ_RULES | wxDV_VERT_RULES | wxDV_ROW_LINES | wxDV_SINGLE){
	AppendTextColumn(wxT("�t�B�[���h����(m)"),		 wxDATAVIEW_CELL_EDITABLE,  95);
	AppendTextColumn(wxT("�t�B�[���h�c��(m)"),		 wxDATAVIEW_CELL_EDITABLE,  95);
	AppendTextColumn(wxT("�V�~�����[�V��������(s)"), wxDATAVIEW_CELL_EDITABLE, 120);
	AppendTextColumn(wxT("�ʐM���x(bps)"),			 wxDATAVIEW_CELL_EDITABLE,  90);
	AppendTextColumn(wxT("�ʐM�\�͈�(m)"),		 wxDATAVIEW_CELL_EDITABLE, 105);
	AppendTextColumn(wxT("���b�Z�[�W��(bit)"),		 wxDATAVIEW_CELL_EDITABLE,  95);
	AppendTextColumn(wxT("���b�Z�[�W�Ԋu(s)"),		 wxDATAVIEW_CELL_EDITABLE, 100);
	AppendTextColumn(wxT("�����[�m�[�h��"),			 wxDATAVIEW_CELL_EDITABLE,  80);
	AppendTextColumn(wxT("���[�e�B���O�v���g�R��"),  wxDATAVIEW_CELL_EDITABLE, 110);
	Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &EnvironmentsPage::EnvironmentsList::onSelectionChanged, 
		 this, static_cast<int>(ComponentID::LIST));
	Bind(wxEVT_DATAVIEW_ITEM_EDITING_DONE, &EnvironmentsPage::EnvironmentsList::onEditingDone,
		this, static_cast<int>(ComponentID::LIST));
}

void EnvironmentsPage::EnvironmentsList::onSelectionChanged(wxDataViewEvent& event){
}

void EnvironmentsPage::EnvironmentsList::onEditingDone(wxDataViewEvent& event){
	const auto val = event.GetValue();
	const auto col = event.GetColumn();
	// TODO::validation
}