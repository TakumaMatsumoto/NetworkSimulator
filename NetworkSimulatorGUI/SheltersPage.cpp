#include "SheltersPage.h"
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

SheltersPage::SheltersPage(wxNotebook* p_parent) : wxPanel(p_parent, wxID_ANY){
	mp_list_ctrl = new SheltersList(this);
	mp_add_item_button = new wxButton(this, static_cast<int>(Command::ADD_ITEM), "追加");
	mp_delete_item_button = new wxButton(this, static_cast<int>(Command::DELETE_ITEM), "削除");
	mp_load_items_button = new wxButton(this, static_cast<int>(Command::LOAD_ITEMS), "読み込み");
	mp_save_items_button = new wxButton(this, static_cast<int>(Command::SAVE_ITEMS), "名前を付けて保存");
	Connect(static_cast<int>(Command::ADD_ITEM), wxEVT_COMMAND_BUTTON_CLICKED
		, wxCommandEventHandler(SheltersPage::onAddItem));
	Connect(static_cast<int>(Command::DELETE_ITEM), wxEVT_COMMAND_BUTTON_CLICKED
		, wxCommandEventHandler(SheltersPage::onDeleteItem));
	Connect(static_cast<int>(Command::LOAD_ITEMS), wxEVT_COMMAND_BUTTON_CLICKED
		, wxCommandEventHandler(SheltersPage::onLoadItems));
	Connect(static_cast<int>(Command::SAVE_ITEMS), wxEVT_COMMAND_BUTTON_CLICKED
		, wxCommandEventHandler(SheltersPage::onSaveItems));

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

void SheltersPage::onAddItem(wxCommandEvent& event){
}

void SheltersPage::onDeleteItem(wxCommandEvent & event){

}

void SheltersPage::onLoadItems(wxCommandEvent & event){

}

void SheltersPage::onSaveItems(wxCommandEvent & event){

}

SheltersPage::SheltersList::SheltersList(wxWindow* p_parent) :
wxListCtrl(p_parent, wxID_ANY, wxDefaultPosition, p_parent->GetSize(), wxLC_REPORT | wxLC_VIRTUAL){
	InsertColumn(static_cast<long>(Columns::X_POSITION), wxT("X座標"));
	InsertColumn(static_cast<long>(Columns::Y_POSITION), wxT("Y座標"));
	for (int i = 0; i < GetColumnCount(); i++)
	{
		SetColumnWidth(i, 200);
	}
}

wxString SheltersPage::SheltersList::OnGetItemText(long item, long column) const{
	return GetItemText(item, column);
}