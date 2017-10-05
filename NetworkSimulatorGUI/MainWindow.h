#pragma once

class MainWindow : public wxFrame
{
private:
	wxSlider* mp_slider;
	wxStaticText* mp_time_label;
	// Commands begin
	void onNewProject(wxCommandEvent& event);
	void onExportResults(wxCommandEvent& event);
	void onExit(wxCommandEvent& event);
	void onOpenSettingWindow(wxCommandEvent& event);
	void onExecuteWithGraphicUpdate(wxCommandEvent& event);
	void onExecuteWithoutGraphicUpdate(wxCommandEvent& event);
	void onStop(wxCommandEvent& event);
	void onAbout(wxCommandEvent& event);
	// Commands end
	class FileMenu : public wxMenu{
	public:
		FileMenu(MainWindow* p_parent);
	};
	class ExecuteMenu : public wxMenu{
		wxMenuItem* mp_execute_with_graphic_update_menu_item;
		wxMenuItem* mp_execute_without_graphic_update_menu_item;
		wxMenuItem* mp_stop_menu_item;
		MainWindow* mp_window;
	public:
		ExecuteMenu(MainWindow* p_parent);
	};
	class HelpMenu : public wxMenu{
	public:
		HelpMenu(MainWindow* p_parent);
	};
public:
	MainWindow();
};
