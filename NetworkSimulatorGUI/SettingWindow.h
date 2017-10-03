#pragma once

class SettingWindow : public wxDialog{
public:
	SettingWindow(wxWindow * parent, wxWindowID id, const wxString & title,
		const wxPoint & pos = wxDefaultPosition,
		const wxSize & size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE);

private:

	void OnOk(wxCommandEvent & event);
};