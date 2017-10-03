#pragma once

class MainWindow : public wxFrame
{
private:
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
	class IMenu{
	public:
		virtual ~IMenu() = default;
		virtual wxMenu* create() = 0;
	};
	class FileMenu : public IMenu{
		MainWindow* mp_window;
	public:
		FileMenu(MainWindow* p_window) : mp_window(p_window){

		}
		wxMenu* create() override;
	};
	class ExecuteMenu : public IMenu{
		wxMenuItem* mp_execute_with_graphic_update_menu_item;
		wxMenuItem* mp_execute_without_graphic_update_menu_item;
		wxMenuItem* mp_stop_menu_item;
		MainWindow* mp_window;
	public:
		ExecuteMenu(MainWindow* p_window) : mp_window(p_window){

		}
		wxMenu* create() override;
	};
	class HelpMenu : public IMenu{
		MainWindow* mp_window;
	public:
		HelpMenu(MainWindow* p_window) : mp_window(p_window){

		}
		wxMenu* create() override;
	};
public:
	MainWindow();
};
