#include "MainWindow.h"

MainWindow::MainWindow()
	: wxFrame(NULL, wxID_ANY, "NetworkSimulator", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	Centre();

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(FileMenu(this).create(),	 "&�t�@�C��");
	menuBar->Append(ExecuteMenu(this).create(),  "&�V�~�����[�V����");
	menuBar->Append(HelpMenu(this).create(),	 "&�w���v");
	SetBackgroundColour(wxColor(255, 255, 255));
	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Wait...");
}

void MainWindow::onNewProject(wxCommandEvent& event){

}

void MainWindow::onExportResults(wxCommandEvent& event){

}

void MainWindow::onExit(wxCommandEvent& event){
	Close(true);
}

void MainWindow::onOpenSettingWindow(wxCommandEvent& event){

}

void MainWindow::onExecuteWithoutGraphicUpdate(wxCommandEvent& event){

}

void MainWindow::onExecuteWithGraphicUpdate(wxCommandEvent& event){

}

void MainWindow::onStop(wxCommandEvent& event){

}

void MainWindow::onAbout(wxCommandEvent& event){
	wxMessageBox("NetworkSimulator ver 0.1",
		"NetworkSimulator�̃o�[�W�������", wxOK | wxICON_INFORMATION);
}
