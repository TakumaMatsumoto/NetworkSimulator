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
	ret->Append(ID_NEW, "&新しいプロジェクト\tCtrl+N");
	ret->AppendSeparator();
	ret->Append(ID_EXPORT, "&結果を保存\tCtrl+S");
	ret->AppendSeparator();
	ret->Append(ID_EXIT, "&終了\tAlt+F4");
	mp_window->Bind(wxEVT_MENU, &MainWindow::onNewProject,		mp_window, ID_NEW);
	mp_window->Bind(wxEVT_MENU, &MainWindow::onExportResults,	mp_window, ID_EXPORT);
	mp_window->Bind(wxEVT_MENU, &MainWindow::onExit,			mp_window, ID_EXIT);
	return ret;
}

wxMenu* MainWindow::ExecuteMenu::create(){
	wxMenu* ret = new wxMenu;
	mp_execute_with_graphic_update_menu_item = new wxMenuItem(NULL, ID_EXECUTE_WITH_GRAPHIC_UPDATE, "&リアルタイム表示ありで実行\tF7");
	mp_execute_without_graphic_update_menu_item = new wxMenuItem(NULL, ID_EXECUTE_WITHOUT_GRAPHIC_UPDATE, "&リアルタイム表示なしで実行\tF8");
	mp_stop_menu_item = new wxMenuItem(NULL, ID_STOP, "&停止\tF9");
	mp_stop_menu_item->Enable(false);

	ret->Append(ID_OPEN_SETTING_WINDOW, "&設定ウィンドウを開く\tCtrl+T");
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
	ret->Append(ID_ABOUT, "&バージョン情報\tCtrl+Q");
	mp_window->Bind(wxEVT_MENU, &MainWindow::onAbout, mp_window, ID_ABOUT);
	return ret;
}