#pragma once

class SheltersPage : public wxPanel{
	class SheltersList : public wxListCtrl{
	public:
		SheltersList(wxWindow* p_parent);
		wxString OnGetItemText(long item, long column) const;
	};
	wxListCtrl* mp_list_ctrl;
	wxButton* mp_add_item_button;
	wxButton* mp_delete_item_button;
	wxButton* mp_load_items_button;
	wxButton* mp_save_items_button;
	void onAddItem(wxCommandEvent & event);
	void onDeleteItem(wxCommandEvent & event);
	void onLoadItems(wxCommandEvent & event);
	void onSaveItems(wxCommandEvent & event);
	SheltersPage(wxNotebook* p_parent);
	friend class SettingWindow;
};
