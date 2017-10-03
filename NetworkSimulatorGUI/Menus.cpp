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

wxMenu* Window::FileMenu::create(){
	wxMenu* ret = new wxMenu;
	ret->Append(ID_NEW, "&�V�����v���W�F�N�g\tCtrl+N");
	ret->AppendSeparator();
	ret->Append(ID_EXPORT, "&���ʂ��G�N�X�|�[�g\tCtrl+E");
	ret->AppendSeparator();
	ret->Append(ID_EXIT, "&�I��\tAlt+F4");
	mp_window->Bind(wxEVT_MENU, &Window::onNewProject,	mp_window, ID_NEW);
	mp_window->Bind(wxEVT_MENU, &Window::onExport,		mp_window, ID_EXPORT);
	mp_window->Bind(wxEVT_MENU, &Window::onExit,		mp_window, ID_EXIT);
	return ret;
}

wxMenu* Window::SettingMenu::create(){
	wxMenu* ret = new wxMenu;
	ret->Append(ID_OPEN, "&�t�@�C�����J��\tCtrl+O");
	ret->AppendSeparator();
	ret->Append(ID_SAVE, "&�㏑���ۑ�\tCtrl+S");
	ret->Append(ID_SAVE_AS, "&���O��t���ĕۑ�\tCtrl+Shift+S");
	ret->AppendSeparator();
	ret->Append(ID_EDIT, "&�ݒ�E�B���h�E���J��\tCtrl+T");
	mp_window->Bind(wxEVT_MENU, &Window::onOpen, mp_window, ID_OPEN);
	mp_window->Bind(wxEVT_MENU, &Window::onSave, mp_window, ID_SAVE);
	mp_window->Bind(wxEVT_MENU, &Window::onSaveAs, mp_window, ID_SAVE_AS);
	return ret;
}

wxMenu* Window::ExecuteMenu::create(){
	wxMenu* ret = new wxMenu;
	mp_execute_with_graphic_update_menu_item = new wxMenuItem(NULL, ID_EXECUTE_WITH_GRAPHIC_UPDATE, "&���A���^�C���\������Ŏ��s\tF7");
	mp_execute_without_graphic_update_menu_item = new wxMenuItem(NULL, ID_EXECUTE_WITHOUT_GRAPHIC_UPDATE, "&���A���^�C���\���Ȃ��Ŏ��s\tF8");
	mp_stop_menu_item = new wxMenuItem(NULL, ID_STOP, "&��~\tF9");
	mp_stop_menu_item->Enable(false);

	ret->Append(mp_execute_with_graphic_update_menu_item);
	ret->Append(mp_execute_without_graphic_update_menu_item);
	ret->Append(mp_stop_menu_item);
	mp_window->Bind(wxEVT_MENU, &Window::onExecuteWithGraphicUpdate,	mp_window, ID_EXECUTE_WITH_GRAPHIC_UPDATE);
	mp_window->Bind(wxEVT_MENU, &Window::onExecuteWithoutGraphicUpdate, mp_window, ID_EXECUTE_WITHOUT_GRAPHIC_UPDATE);
	mp_window->Bind(wxEVT_MENU, &Window::onStop,						mp_window, ID_STOP);
	return ret;
}

wxMenu* Window::HelpMenu::create(){
	wxMenu* ret = new wxMenu;
	ret->Append(ID_ABOUT, "&�o�[�W�������\tCtrl+Q");
	mp_window->Bind(wxEVT_MENU, &Window::onAbout, mp_window, ID_ABOUT);
	return ret;
}