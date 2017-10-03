#include "Window.h"

Window::Window()
	: wxFrame(NULL, wxID_ANY, "NetworkSimulator", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	Centre();

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(FileMenu(this).create(),	 "&ファイル");
	menuBar->Append(SettingMenu(this).create(),	 "&設定");
	menuBar->Append(ExecuteMenu(this).create(),  "&実行");
	menuBar->Append(HelpMenu(this).create(),	 "&ヘルプ");
	SetBackgroundColour(wxColor(255, 255, 255));
	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Wait...");
}

void Window::onNewProject(wxCommandEvent& event){

}

void Window::onExport(wxCommandEvent& event){

}

void Window::onExit(wxCommandEvent& event){
	Close(true);
}

void Window::onOpen(wxCommandEvent& event){

}

void Window::onSave(wxCommandEvent& event){

}

void Window::onSaveAs(wxCommandEvent& event){

}

void Window::onEdit(wxCommandEvent& event){

}

void Window::onExecuteWithoutGraphicUpdate(wxCommandEvent& event){

}

void Window::onExecuteWithGraphicUpdate(wxCommandEvent& event){

}

void Window::onStop(wxCommandEvent& event){

}

void Window::onAbout(wxCommandEvent& event){
	wxMessageBox("NetworkSimulator ver 0.1",
		"NetworkSimulatorのバージョン情報", wxOK | wxICON_INFORMATION);
}
