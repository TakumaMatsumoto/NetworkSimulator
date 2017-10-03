#pragma once

class Window : public wxFrame
{
private:
	// Commands begin
	void onNewProject(wxCommandEvent& event);
	void onExport(wxCommandEvent& event);
	void onExit(wxCommandEvent& event);
	void onOpen(wxCommandEvent& event);
	void onSave(wxCommandEvent& event);
	void onSaveAs(wxCommandEvent& event);
	void onEdit(wxCommandEvent& event);
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
		Window* mp_window;
	public:
		FileMenu(Window* p_window) : mp_window(p_window){

		}
		wxMenu* create() override;
	};
	class SettingMenu : public IMenu{
		Window* mp_window;
	public:
		SettingMenu(Window* p_window) : mp_window(p_window){

		}
		wxMenu* create() override;
	};
	class ExecuteMenu : public IMenu{
		wxMenuItem* mp_execute_with_graphic_update_menu_item;
		wxMenuItem* mp_execute_without_graphic_update_menu_item;
		wxMenuItem* mp_stop_menu_item;
		Window* mp_window;
	public:
		ExecuteMenu(Window* p_window) : mp_window(p_window){

		}
		wxMenu* create() override;
	};
	class HelpMenu : public IMenu{
		Window* mp_window;
	public:
		HelpMenu(Window* p_window) : mp_window(p_window){

		}
		wxMenu* create() override;
	};
public:
	Window();
};
