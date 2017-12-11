#include <wx/aui/auibook.h>
#include "SettingWindow.h"
#include "EnvironmentsPage.h"
#include "SheltersPage.h"
#include "SufferersPage.h"

SettingWindow::SettingWindow(wxWindow * parent, wxWindowID id)
	: wxDialog(parent, id, "�ݒ�", wxDefaultPosition, wxSize(900, 300), wxDEFAULT_DIALOG_STYLE)
{
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxNotebook* notebook = new wxNotebook(panel, wxID_ANY);
	// 1�y�[�W��(�t�B�[���h�̑傫���Ȃǂ̐ݒ�)
	notebook->AddPage(new EnvironmentsPage(notebook), "��");
	// 2�y�[�W��(�V�F���^�[�Ɋւ���ݒ�)
	notebook->AddPage(new SheltersPage(notebook), "�V�F���^�[");
	// 3�y�[�W��(��Ў҂Ɋւ���ݒ�)
	notebook->AddPage(new SufferersPage(notebook), "��Ў�");

	// NoteBook�p��BoxSizer
	wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
	panelSizer->Add(notebook, 1, wxEXPAND);
	panel->SetSizer(panelSizer);
	// �_�C�A���O�S�̂�BoxSizer
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->SetMinSize(this->GetSize());
	topSizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(topSizer);
}