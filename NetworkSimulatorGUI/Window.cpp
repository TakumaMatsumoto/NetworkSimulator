#include "Window.h"

Window::Window()
	: wxFrame(NULL, wxID_ANY, "NetworkSimulator", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	Centre();

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(FileMenu(this).create(),	 "&�t�@�C��");
	menuBar->Append(SettingMenu(this).create(),	 "&�ݒ�");
	menuBar->Append(ExecuteMenu(this).create(),  "&���s");
	menuBar->Append(HelpMenu(this).create(),	 "&�w���v");
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
		"NetworkSimulator�̃o�[�W�������", wxOK | wxICON_INFORMATION);
}
