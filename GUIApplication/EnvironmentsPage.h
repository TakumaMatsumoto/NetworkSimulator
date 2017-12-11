#pragma once

class EnvironmentsPage : public wxPanel{
	class EnvironmentsList : public wxDataViewListCtrl{
		void onSelectionChanged(wxDataViewEvent& event);
		void onEditingDone(wxDataViewEvent& event);
	public:
		EnvironmentsList(wxWindow* p_parent);
	};
	wxDataViewListCtrl* mp_list_ctrl;
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