#include "MainWindow.h"
#include "SettingWindow.h"
#include "Canvas.h"
#include "App.h"

MainWindow::MainWindow()
	: wxFrame(NULL, wxID_ANY, "NetworkSimulator", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	mp_slider = new wxSlider(this, 1, 0, 0, 1, wxPoint(0, 0), wxSize(500, -1));
	mp_time_label = new wxStaticText(this, 1, "Time:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	mp_time_label->SetFont(wxFont(20, wxFontFamily::wxFONTFAMILY_ROMAN, wxNORMAL, wxNORMAL));

	// �S�̂̃p�l��
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	// �ŉ����̃p�l��
	wxBoxSizer* bottomSizer = new wxBoxSizer(wxHORIZONTAL);

	// �V�~�����[�V�����󋵕\���p�L�����o�X
	topSizer->Add(new Canvas(this), 1, wxEXPAND | wxALL, 2);
	// ���E����ǉ�
	auto panel = new wxPanel(this, 0, 0, GetClientSize().GetWidth(), 2);
	panel->SetBackgroundColour("#000000");
	topSizer->Add(panel);
	// ���݂̎����A�X���C�_�[��ǉ�
	bottomSizer->Add(mp_time_label, 1, wxALIGN_RIGHT);
	bottomSizer->Add(mp_slider, 1, wxEXPAND);
	topSizer->Add(bottomSizer);

	SetSizer(topSizer);

	// ���j���[�Ɋւ��鏉����
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(new FileMenu(this),		"&�t�@�C��");
	menuBar->Append(new ExecuteMenu(this),  "&�V�~�����[�V����");
	menuBar->Append(new HelpMenu(this),		"&�w���v");
	SetMenuBar(menuBar);

	// �E�B���h�E���̂̐ݒ�
	Centre();
	SetBackgroundColour(wxColor(255, 255, 255));
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
	SettingWindow diag(this, -1);
	diag.ShowModal();
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
