#include <wx/aui/auibook.h>
#include "SettingWindow.h"
#include "EnvironmentsList.h"
enum class Command{
	ADD_ITEM = 0,
	DELETE_ITEM,
	LOAD_ITEMS,
	SAVE_ITEMS
};

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
	notebook->AddPage(new EnvironmentsPage(notebook), "��Ў�");

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

SettingWindow::EnvironmentsPage::EnvironmentsPage(wxNotebook* p_parent) : wxPanel(p_parent, wxID_ANY){
	mp_add_item_button = new wxButton(this, wxID_ANY, "�ǉ�");
	mp_delete_item_button = new wxButton(this, wxID_ANY, "�폜");
	mp_load_items_button = new wxButton(this, wxID_ANY, "�ǂݍ���");
	mp_save_items_button = new wxButton(this, wxID_ANY, "���O��t���ĕۑ�");

	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(new EnvironmentsList(this), 5, wxEXPAND);

	wxBoxSizer* bottomSizer = new wxBoxSizer(wxHORIZONTAL);
	bottomSizer->Add(mp_add_item_button, 1, wxEXPAND);
	bottomSizer->Add(mp_delete_item_button, 1, wxEXPAND);
	bottomSizer->Add(mp_load_items_button, 1, wxEXPAND);
	bottomSizer->Add(mp_save_items_button, 1, wxEXPAND);
	topSizer->Add(bottomSizer, 1, wxSHAPED);
	SetSizer(topSizer);
}

void SettingWindow::EnvironmentsPage::OnAdd(wxCommandEvent & event){

}

SettingWindow::SheltersPage::SheltersPage(wxNotebook* p_parent) : wxPanel(p_parent, wxID_ANY){
	wxTextCtrl* textCtrl2 = new wxTextCtrl(this, wxID_ANY, L"Tab 2 Contents");
}

SettingWindow::SufferersPage::SufferersPage(wxNotebook* p_parent) : wxPanel(p_parent, wxID_ANY){
	wxTextCtrl* textCtrl3 = new wxTextCtrl(this, wxID_ANY, L"Tab 2 Contents");
}