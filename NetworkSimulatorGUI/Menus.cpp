#include "Window.h"

enum{
	ID_NEW = 1,
	ID_EXPORT = 2,
	ID_EXIT = 3,
	ID_OPEN = 4,
	ID_SAVE = 5,
	ID_SAVE_AS = 6,
	ID_EDIT = 7,
	ID_EXECUTE_WITHOUT_GRAPHIC_UPDATE = 8,
	ID_EXECUTE_WITH_GRAPHIC_UPDATE = 9,
	ID_STOP = 10,
	ID_ABOUT = 11,
};

wxMenu* Window::createFileMenu(){
	wxMenu* ret = new wxMenu;
	ret->Append(ID_NEW, "&�V�����v���W�F�N�g\tCtrl+N");
	ret->AppendSeparator();
	ret->Append(ID_EXPORT, "&���ʂ��G�N�X�|�[�g\tCtrl+E");
	ret->AppendSeparator();
	ret->Append(ID_EXIT, "&�I��\tAlt+F4");
	Bind(wxEVT_MENU, &Window::OnNewProject, this, ID_NEW);
	Bind(wxEVT_MENU, &Window::OnExport,		this, ID_EXPORT);
	Bind(wxEVT_MENU, &Window::OnExit,		this, ID_EXIT);
	return ret;
}

wxMenu* Window::createSettingMenu(){
	wxMenu* ret = new wxMenu;
	ret->Append(ID_OPEN, "&�t�@�C�����J��\tCtrl+O");
	ret->AppendSeparator();
	ret->Append(ID_SAVE, "&�㏑���ۑ�\tCtrl+S");
	ret->Append(ID_SAVE_AS, "&���O��t���ĕۑ�\tCtrl+Shift+S");
	ret->AppendSeparator();
	ret->Append(ID_EDIT, "&�ݒ�E�B���h�E���J��\tCtrl+T");
	Bind(wxEVT_MENU, &Window::OnOpen,	this, ID_OPEN);
	Bind(wxEVT_MENU, &Window::OnSave,	this, ID_SAVE);
	Bind(wxEVT_MENU, &Window::OnSaveAs, this, ID_SAVE_AS);
	return ret;
}

wxMenu* Window::createExecuteMenu(){
	wxMenu* ret = new wxMenu;
	mp_execute_with_graphic_update_menu_item = new wxMenuItem(NULL, ID_EXECUTE_WITH_GRAPHIC_UPDATE, "&���A���^�C���\������Ŏ��s\tF7");
	mp_execute_without_graphic_update_menu_item = new wxMenuItem(NULL, ID_EXECUTE_WITHOUT_GRAPHIC_UPDATE, "&���A���^�C���\���Ȃ��Ŏ��s\tF8");
	mp_stop_menu_item = new wxMenuItem(NULL, ID_STOP, "&��~\tF9");
	mp_stop_menu_item->Enable(false);

	ret->Append(mp_execute_with_graphic_update_menu_item);
	ret->Append(mp_execute_without_graphic_update_menu_item);
	ret->Append(mp_stop_menu_item);
	Bind(wxEVT_MENU, &Window::OnExecuteWithGraphicUpdate,	 this, ID_EXECUTE_WITH_GRAPHIC_UPDATE);
	Bind(wxEVT_MENU, &Window::OnExecuteWithoutGraphicUpdate, this, ID_EXECUTE_WITHOUT_GRAPHIC_UPDATE);
	Bind(wxEVT_MENU, &Window::OnStop,						 this, ID_STOP);
	return ret;
}

wxMenu* Window::createHelpMenu(){
	wxMenu* ret = new wxMenu;
	ret->Append(ID_ABOUT, "&�o�[�W�������\tCtrl+Q");
	Bind(wxEVT_MENU, &Window::OnAbout, this, ID_ABOUT);
	return ret;
}

void Window::OnNewProject(wxCommandEvent& event){

}

void Window::OnExport(wxCommandEvent& event){

}

void Window::OnExit(wxCommandEvent& event){
	Close(true);
}

void Window::OnOpen(wxCommandEvent& event){

}

void Window::OnSave(wxCommandEvent& event){

}

void Window::OnSaveAs(wxCommandEvent& event){

}

void Window::OnEdit(wxCommandEvent& event){

}

void Window::OnExecuteWithoutGraphicUpdate(wxCommandEvent& event){

}

void Window::OnExecuteWithGraphicUpdate(wxCommandEvent& event){

}

void Window::OnStop(wxCommandEvent& event){

}

void Window::OnAbout(wxCommandEvent& event){
	wxMessageBox("NetworkSimulator ver 0.1",
		"NetworkSimulator�̃o�[�W�������", wxOK | wxICON_INFORMATION);
}
