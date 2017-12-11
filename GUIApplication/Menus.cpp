#include "MainWindow.h"

enum class Command{
	NEW = 0,
	EXPORT,
	EXIT,
	OPEN_SETTING_WINDOW,
	EXECUTE_WITHOUT_GRAPHIC_UPDATE,
	EXECUTE_WITH_GRAPHIC_UPDATE,
	STOP,
	ABOUT
};

MainWindow::FileMenu::FileMenu(MainWindow* p_parent){
	Append(static_cast<int>(Command::NEW), "&新しいプロジェクト\tCtrl+N");
	AppendSeparator();
	Append(static_cast<int>(Command::EXPORT), "&結果を保存\tCtrl+S");
	AppendSeparator();
	Append(static_cast<int>(Command::EXIT), "&終了\tAlt+F4");
	p_parent->Bind(wxEVT_MENU, &MainWindow::onNewProject,		p_parent, static_cast<int>(Command::NEW));
	p_parent->Bind(wxEVT_MENU, &MainWindow::onExportResults,	p_parent, static_cast<int>(Command::EXPORT));
	p_parent->Bind(wxEVT_MENU, &MainWindow::onExit,				p_parent, static_cast<int>(Command::EXIT));
}

MainWindow::ExecuteMenu::ExecuteMenu(MainWindow* p_parent){
	mp_execute_with_graphic_update_menu_item =		new wxMenuItem(NULL, static_cast<int>(Command::EXECUTE_WITH_GRAPHIC_UPDATE), "&リアルタイム表示ありで実行\tF7");
	mp_execute_without_graphic_update_menu_item =	new wxMenuItem(NULL, static_cast<int>(Command::EXECUTE_WITHOUT_GRAPHIC_UPDATE), "&リアルタイム表示なしで実行\tF8");
	mp_stop_menu_item =								new wxMenuItem(NULL, static_cast<int>(Command::STOP), "&停止\tF9");
	mp_stop_menu_item->Enable(false);

	Append(static_cast<int>(Command::OPEN_SETTING_WINDOW), "&設定ウィンドウを開く\tCtrl+T");
	AppendSeparator();
	Append(mp_execute_with_graphic_update_menu_item);
	Append(mp_execute_without_graphic_update_menu_item);
	Append(mp_stop_menu_item);
	p_parent->Bind(wxEVT_MENU, &MainWindow::onOpenSettingWindow,			p_parent, static_cast<int>(Command::OPEN_SETTING_WINDOW));
	p_parent->Bind(wxEVT_MENU, &MainWindow::onExecuteWithGraphicUpdate,		p_parent, static_cast<int>(Command::EXECUTE_WITH_GRAPHIC_UPDATE));
	p_parent->Bind(wxEVT_MENU, &MainWindow::onExecuteWithoutGraphicUpdate,	p_parent, static_cast<int>(Command::EXECUTE_WITHOUT_GRAPHIC_UPDATE));
	p_parent->Bind(wxEVT_MENU, &MainWindow::onStop,							p_parent, static_cast<int>(Command::STOP));
}

MainWindow::HelpMenu::HelpMenu(MainWindow* p_parent){
	Append(static_cast<int>(Command::ABOUT), "&バージョン情報\tCtrl+Q");
	p_parent->Bind(wxEVT_MENU, &MainWindow::onAbout, p_parent, static_cast<int>(Command::ABOUT));
}