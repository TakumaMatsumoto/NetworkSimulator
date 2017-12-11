#include <wx/aui/auibook.h>
#include "SettingWindow.h"
#include "EnvironmentsPage.h"
#include "SheltersPage.h"
#include "SufferersPage.h"

SettingWindow::SettingWindow(wxWindow * parent, wxWindowID id)
	: wxDialog(parent, id, "設定", wxDefaultPosition, wxSize(900, 300), wxDEFAULT_DIALOG_STYLE)
{
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxNotebook* notebook = new wxNotebook(panel, wxID_ANY);
	// 1ページ目(フィールドの大きさなどの設定)
	notebook->AddPage(new EnvironmentsPage(notebook), "環境");
	// 2ページ目(シェルターに関する設定)
	notebook->AddPage(new SheltersPage(notebook), "シェルター");
	// 3ページ目(被災者に関する設定)
	notebook->AddPage(new SufferersPage(notebook), "被災者");

	// NoteBook用のBoxSizer
	wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
	panelSizer->Add(notebook, 1, wxEXPAND);
	panel->SetSizer(panelSizer);
	// ダイアログ全体のBoxSizer
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->SetMinSize(this->GetSize());
	topSizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(topSizer);
}