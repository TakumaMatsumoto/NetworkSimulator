#include "MainWindow.h"

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

wxMenu* MainWindow::FileMenu::create(){
	wxMenu* ret = new wxMenu;
	ret->Append(ID_NEW, "&新しいプロジェクト\tCtrl+N");
	ret->AppendSeparator();
	ret->Append(ID_EXPORT, "&結果をエクスポート\tCtrl+E");
	ret->AppendSeparator();
	ret->Append(ID_EXIT, "&終了\tAlt+F4");
	mp_window->Bind(wxEVT_MENU, &MainWindow::onNewProject,		mp_window, ID_NEW);
	mp_window->Bind(wxEVT_MENU, &MainWindow::onExportResults,	mp_window, ID_EXPORT);
	mp_window->Bind(wxEVT_MENU, &MainWindow::onExit,			mp_window, ID_EXIT);
	return ret;
}

wxMenu* MainWindow::SettingMenu::create(){
	wxMenu* ret = new wxMenu;
	ret->Append(ID_OPEN, "&ファイルを開く\tCtrl+O");
	ret->AppendSeparator();
	ret->Append(ID_SAVE, "&上書き保存\tCtrl+S");
	ret->Append(ID_SAVE_AS, "&名前を付けて保存\tCtrl+Shift+S");
	ret->AppendSeparator();
	ret->Append(ID_EDIT, "&設定ウィンドウを開く\tCtrl+T");
	mp_window->Bind(wxEVT_MENU, &MainWindow::onOpen, mp_window, ID_OPEN);
	mp_window->Bind(wxEVT_MENU, &MainWindow::onSave, mp_window, ID_SAVE);
	mp_window->Bind(wxEVT_MENU, &MainWindow::onSaveAs, mp_window, ID_SAVE_AS);
	return ret;
}

wxMenu* MainWindow::ExecuteMenu::create(){
	wxMenu* ret = new wxMenu;
	mp_execute_with_graphic_update_menu_item = new wxMenuItem(NULL, ID_EXECUTE_WITH_GRAPHIC_UPDATE, "&リアルタイム表示ありで実行\tF7");
	mp_execute_without_graphic_update_menu_item = new wxMenuItem(NULL, ID_EXECUTE_WITHOUT_GRAPHIC_UPDATE, "&リアルタイム表示なしで実行\tF8");
	mp_stop_menu_item = new wxMenuItem(NULL, ID_STOP, "&停止\tF9");
	mp_stop_menu_item->Enable(false);

	ret->Append(mp_execute_with_graphic_update_menu_item);
	ret->Append(mp_execute_without_graphic_update_menu_item);
	ret->Append(mp_stop_menu_item);
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