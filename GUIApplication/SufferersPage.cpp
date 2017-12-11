#include "SufferersPage.h"
#include "Config.h"

enum class Command{
	ADD_ITEM = 0,
	DELETE_ITEM,
	LOAD_ITEMS,
	SAVE_ITEMS
};

enum class Columns{
	X_POSITION = 0,
	Y_POSITION
};

SufferersPage::SufferersPage(wxNotebook* p_parent) : wxPanel(p_parent, wxID_ANY){
	mp_list_ctrl = new SufferersList(this);
	mp_add_item_button = new wxButton(this, static_cast<int>(Command::ADD_ITEM), "追加");
	mp_delete_item_button = new wxButton(this, static_cast<int>(Command::DELETE_ITEM), "削除");
	mp_load_items_button = new wxButton(this, static_cast<int>(Command::LOAD_ITEMS), "読み込み");
	mp_save_items_button = new wxButton(this, static_cast<int>(Command::SAVE_ITEMS), "名前を付けて保存");
	Connect(static_cast<int>(Command::ADD_ITEM), wxEVT_COMMAND_BUTTON_CLICKED
		, wxCommandEventHandler(SufferersPage::onAddItem));
	Connect(static_cast<int>(Command::DELETE_ITEM), wxEVT_COMMAND_BUTTON_CLICKED
		, wxCommandEventHandler(SufferersPage::onDeleteItem));
	Connect(static_cast<int>(Command::LOAD_ITEMS), wxEVT_COMMAND_BUTTON_CLICKED
		, wxCommandEventHandler(SufferersPage::onLoadItems));
	Connect(static_cast<int>(Command::SAVE_ITEMS), wxEVT_COMMAND_BUTTON_CLICKED
		, wxCommandEventHandler(SufferersPage::onSaveItems));

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

void SufferersPage::onAddItem(wxCommandEvent& event){
	const int index = mp_list_ctrl->GetItemCount();
	mp_list_ctrl->InsertItem(index, wxString("0"));
	const ns::Config def = ns::Config();
	mp_list_ctrl->SetItem(index, static_cast<long>(Columns::X_POSITION), std::to_string(def.m_area.getWidth()));
	mp_list_ctrl->SetItem(index, static_cast<long>(Columns::Y_POSITION), std::to_string(def.m_area.getHeight()));
}

void SufferersPage::onDeleteItem(wxCommandEvent & event){

}

void SufferersPage::onLoadItems(wxCommandEvent & event){

}

void SufferersPage::onSaveItems(wxCommandEvent & event){

}

SufferersPage::SufferersList::SufferersList(wxWindow* p_parent) :
wxListCtrl(p_parent, wxID_ANY, wxDefaultPosition, p_parent->GetSize(), wxLC_REPORT | wxLC_VIRTUAL){
	InsertColumn(static_cast<long>(Columns::X_POSITION), wxT("X座標"));
	InsertColumn(static_cast<long>(Columns::Y_POSITION), wxT("Y座標"));
	for (int i = 0; i < GetColumnCount(); i++)
	{
		SetColumnWidth(i, 200);
	}
}

wxString SufferersPage::SufferersList::OnGetItemText(long item, long column) const{
	return GetItemText(item, column);
}