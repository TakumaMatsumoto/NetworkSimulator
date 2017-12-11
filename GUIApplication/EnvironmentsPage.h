#pragma once

class EnvironmentsPage : public wxPanel{
	class EnvironmentsList : public wxListCtrl{
	public:
		EnvironmentsList(wxWindow* p_parent);
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
	EnvironmentsPage(wxNotebook* p_parent);
	friend class SettingWindow;
};