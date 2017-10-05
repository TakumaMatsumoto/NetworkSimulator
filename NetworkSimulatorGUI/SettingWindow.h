#pragma once

class SettingWindow : public wxDialog{
private:
	class EnvironmentsPage : public wxPanel{
		wxButton* mp_add_item_button;
		wxButton* mp_delete_item_button;
		wxButton* mp_load_items_button;
		wxButton* mp_save_items_button;
		void OnAdd(wxCommandEvent & event);
	public:
		EnvironmentsPage(wxNotebook* p_parent);
	};
	class SheltersPage : public wxPanel{
	public:
		SheltersPage(wxNotebook* p_parent);
	};
	class SufferersPage : public wxPanel{
	public:
		SufferersPage(wxNotebook* p_parent);
	};

	void OnOk(wxCommandEvent & event);
public:
	SettingWindow(wxWindow * parent, wxWindowID id);
};