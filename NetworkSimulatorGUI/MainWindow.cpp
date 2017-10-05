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

	// 全体のパネル
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	// 最下部のパネル
	wxBoxSizer* bottomSizer = new wxBoxSizer(wxHORIZONTAL);

	// シミュレーション状況表示用キャンバス
	topSizer->Add(new Canvas(this), 1, wxEXPAND | wxALL, 2);
	// 境界線を追加
	auto panel = new wxPanel(this, 0, 0, GetClientSize().GetWidth(), 2);
	panel->SetBackgroundColour("#000000");
	topSizer->Add(panel);
	// 現在の時刻、スライダーを追加
	bottomSizer->Add(mp_time_label, 1, wxALIGN_RIGHT);
	bottomSizer->Add(mp_slider, 1, wxEXPAND);
	topSizer->Add(bottomSizer);

	SetSizer(topSizer);

	// メニューに関する初期化
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(new FileMenu(this),		"&ファイル");
	menuBar->Append(new ExecuteMenu(this),  "&シミュレーション");
	menuBar->Append(new HelpMenu(this),		"&ヘルプ");
	SetMenuBar(menuBar);

	// ウィンドウ自体の設定
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
		"NetworkSimulatorのバージョン情報", wxOK | wxICON_INFORMATION);
}
