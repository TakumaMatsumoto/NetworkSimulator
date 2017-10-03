#include "MainWindow.h"

enum{
	ID_NEW = 1,
	ID_EXPORT = 2,
	ID_EXIT = 3,
	ID_OPEN_SETTING_WINDOW = 4,
	ID_EXECUTE_WITHOUT_GRAPHIC_UPDATE = 5,
	ID_EXECUTE_WITH_GRAPHIC_UPDATE = 6,
	ID_STOP = 7,
	ID_ABOUT = 8,
};

wxMenu* MainWindow::FileMenu::create(){
	wxMenu* ret = new wxMenu;
	ret->Append(ID_NEW, "&�V�����v���W�F�N�g\tCtrl+N");
	ret->AppendSeparator();
	ret->Append(ID_EXPORT, "&���ʂ�ۑ�\tCtrl+S");
	ret->AppendSeparator();
	ret->Append(ID_EXIT, "&�I��\tAlt+F4");
	mp_window->Bind(wxEVT_MENU, &MainWindow::onNewProject,		mp_window, ID_NEW);
	mp_window->Bind(wxEVT_MENU, &MainWindow::onExportResults,	mp_window, ID_EXPORT);
	mp_window->Bind(wxEVT_MENU, &MainWindow::onExit,			mp_window, ID_EXIT);
	return ret;
}

wxMenu* MainWindow::ExecuteMenu::create(){
	wxMenu* ret = new wxMenu;
	mp_execute_with_graphic_update_menu_item = new wxMenuItem(NULL, ID_EXECUTE_WITH_GRAPHIC_UPDATE, "&���A���^�C���\������Ŏ��s\tF7");
	mp_execute_without_graphic_update_menu_item = new wxMenuItem(NULL, ID_EXECUTE_WITHOUT_GRAPHIC_UPDATE, "&���A���^�C���\���Ȃ��Ŏ��s\tF8");
	mp_stop_menu_item = new wxMenuItem(NULL, ID_STOP, "&��~\tF9");
	mp_stop_menu_item->Enable(false);

	ret->Append(ID_OPEN_SETTING_WINDOW, "&�ݒ�E�B���h�E���J��\tCtrl+T");
	ret->AppendSeparator();
	ret->Append(mp_execute_with_graphic_update_menu_item);
	ret->Append(mp_execute_without_graphic_update_menu_item);
	ret->Append(mp_stop_menu_item);
	mp_window->Bind(wxEVT_MENU, &MainWindow::onOpenSettingWindow, mp_window, ID_OPEN_SETTING_WINDOW);
	mp_window->Bind(wxEVT_MENU, &MainWindow::onExecuteWithGraphicUpdate,	mp_window, ID_EXECUTE_WITH_GRAPHIC_UPDATE);
	mp_window->Bind(wxEVT_MENU, &MainWindow::onExecuteWithoutGraphicUpdate, mp_window, ID_EXECUTE_WITHOUT_GRAPHIC_UPDATE);
	mp_window->Bind(wxEVT_MENU, &MainWindow::onStop,						mp_window, ID_STOP);
	return ret;
}

wxMenu* MainWindow::HelpMenu::create(){
	wxMenu* ret = new wxMenu;
	ret->Append(ID_ABOUT, "&�o�[�W�������\tCtrl+Q");
	mp_window->Bind(wxEVT_MENU, &MainWindow::onAbout, mp_window, ID_ABOUT);
	return ret;
}