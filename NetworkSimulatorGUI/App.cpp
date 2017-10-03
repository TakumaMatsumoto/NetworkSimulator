#include "App.h"
#include "Window.h"
#include "Canvas.h"

bool App::OnInit()
{
	mp_frame = new Window();
	mp_slider = new wxSlider(mp_frame, 1, 0, 0, 1, wxPoint(0, 0), wxSize(500, -1));
	mp_time_label = new wxStaticText(mp_frame, 1, "Time:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	mp_time_label->SetFont(wxFont(20, wxFontFamily::wxFONTFAMILY_ROMAN, wxNORMAL, wxNORMAL));

	// 全体のパネル
	wxBoxSizer* entire_sizer = new wxBoxSizer(wxVERTICAL);
	// 最下部のパネル
	wxBoxSizer* bottom_sizer = new wxBoxSizer(wxHORIZONTAL);

	// シミュレーション状況表示用キャンバス
	entire_sizer->Add(new Canvas(mp_frame), 1, wxEXPAND | wxALL, 2);
	// 境界線を追加
	auto panel = new wxPanel(mp_frame, 0, 0, mp_frame->GetClientSize().GetWidth(), 2);
	panel->SetBackgroundColour("#000000");
	entire_sizer->Add(panel);
	// 現在の時刻、スライダーを追加
	bottom_sizer->Add(mp_time_label, 1, wxALIGN_RIGHT);
	bottom_sizer->Add(mp_slider, 1, wxEXPAND);
	entire_sizer->Add(bottom_sizer);

	mp_frame->SetSizer(entire_sizer);
	mp_frame->SetAutoLayout(true);
	mp_frame->Show();

	return true;
}
