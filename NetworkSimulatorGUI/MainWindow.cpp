#include "MainWindow.h"
#include "SettingWindow.h"
#include "Canvas.h"
#include "App.h"

enum class Command{
	SLIDER = 0
};

MainWindow::MainWindow()
	: wxFrame(NULL, wxID_ANY, "NetworkSimulator", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	mp_slider = new wxSlider(this, static_cast<int>(Command::SLIDER), 0, 0, 1, wxPoint(0, 0), wxSize(500, -1));
	mp_time_label = new wxStaticText(this, wxID_ANY, "Time:0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	mp_time_label->SetFont(wxFont(20, wxFontFamily::wxFONTFAMILY_ROMAN, wxNORMAL, wxNORMAL));
	Connect(static_cast<int>(Command::SLIDER), wxEVT_COMMAND_SLIDER_UPDATED,
		wxScrollEventHandler(MainWindow::onScroll));

	// 全体のパネル
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	// シミュレーション状況表示用キャンバス
	topSizer->Add(new Canvas(this), 1, wxEXPAND | wxALL, 2);
	// 境界線を追加
	topSizer->Add([](wxFrame* p_window){
		auto panel = new wxPanel(p_window, wxID_ANY, wxDefaultPosition, wxSize(p_window->GetClientSize().GetWidth(), 2));
		panel->SetBackgroundColour("#000000");
		return panel;
	}(this));
	// 最下部のパネル(現在のシミュレーション内時間、スライダーを表示)
	topSizer->Add([](MainWindow* p_window){
		wxBoxSizer* bottomSizer = new wxBoxSizer(wxHORIZONTAL);
		bottomSizer->Add(p_window->mp_time_label, 1, wxALIGN_RIGHT);
		bottomSizer->Add(p_window->mp_slider, 1, wxEXPAND);
		return bottomSizer;
	}(this));
	// メニューに関する初期化
	SetMenuBar([](MainWindow* p_window){
		wxMenuBar* menuBar = new wxMenuBar;
		menuBar->Append(new FileMenu(p_window), "&ファイル");
		menuBar->Append(new ExecuteMenu(p_window), "&シミュレーション");
		menuBar->Append(new HelpMenu(p_window), "&ヘルプ");
		p_window->SetMenuBar(menuBar);
		return menuBar;
	}(this));

	// ウィンドウ自体の設定
	SetSizer(topSizer);
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

void MainWindow::onScroll(wxScrollEvent& event){
	mp_time_label->SetLabel("Time:" + std::to_string(mp_slider->GetValue()));
}