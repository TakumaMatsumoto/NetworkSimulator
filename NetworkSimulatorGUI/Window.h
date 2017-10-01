#pragma once

class Window : public wxFrame
{
private:
	wxMenuItem* mp_execute_with_graphic_update_menu_item;
	wxMenuItem* mp_execute_without_graphic_update_menu_item;
	wxMenuItem* mp_stop_menu_item;
	wxMenu* createFileMenu();
	wxMenu* createSettingMenu();
	wxMenu* createExecuteMenu();
	wxMenu* createHelpMenu();
	void OnNewProject(wxCommandEvent& event);
	void OnExport(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnSaveAs(wxCommandEvent& event);
	void OnEdit(wxCommandEvent& event);
	void OnExecuteWithGraphicUpdate(wxCommandEvent& event);
	void OnExecuteWithoutGraphicUpdate(wxCommandEvent& event);
	void OnStop(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
public:
	Window();
};
