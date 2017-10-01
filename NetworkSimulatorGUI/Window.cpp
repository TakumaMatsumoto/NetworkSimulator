#include "Window.h"

Window::Window()
	: wxFrame(NULL, wxID_ANY, "NetworkSimulator", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	Centre();

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(createFileMenu(),	 "&�t�@�C��");
	menuBar->Append(createSettingMenu(), "&�ݒ�");
	menuBar->Append(createExecuteMenu(), "&���s");
	menuBar->Append(createHelpMenu(),	 "&�w���v");
	SetBackgroundColour(wxColor(255, 255, 255));
	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Wait...");
}