#include "Window.h"

Window::Window()
	: wxFrame(NULL, wxID_ANY, "NetworkSimulator", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	Centre();

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(createFileMenu(),	 "&ファイル");
	menuBar->Append(createSettingMenu(), "&設定");
	menuBar->Append(createExecuteMenu(), "&実行");
	menuBar->Append(createHelpMenu(),	 "&ヘルプ");
	SetBackgroundColour(wxColor(255, 255, 255));
	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Wait...");
}