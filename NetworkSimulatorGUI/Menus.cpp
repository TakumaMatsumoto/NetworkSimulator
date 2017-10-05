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
	Append(static_cast<int>(Command::NEW), "&�V�����v���W�F�N�g\tCtrl+N");
	AppendSeparator();
	Append(static_cast<int>(Command::EXPORT), "&���ʂ�ۑ�\tCtrl+S");
	AppendSeparator();
	Append(static_cast<int>(Command::EXIT), "&�I��\tAlt+F4");
	p_parent->Bind(wxEVT_MENU, &MainWindow::onNewProject,		p_parent, static_cast<int>(Command::NEW));
	p_parent->Bind(wxEVT_MENU, &MainWindow::onExportResults,	p_parent, static_cast<int>(Command::EXPORT));
	p_parent->Bind(wxEVT_MENU, &MainWindow::onExit,				p_parent, static_cast<int>(Command::EXIT));
}

MainWindow::ExecuteMenu::ExecuteMenu(MainWindow* p_parent){
	mp_execute_with_graphic_update_menu_item =		new wxMenuItem(NULL, static_cast<int>(Command::EXECUTE_WITH_GRAPHIC_UPDATE), "&���A���^�C���\������Ŏ��s\tF7");
	mp_execute_without_graphic_update_menu_item =	new wxMenuItem(NULL, static_cast<int>(Command::EXECUTE_WITHOUT_GRAPHIC_UPDATE), "&���A���^�C���\���Ȃ��Ŏ��s\tF8");
	mp_stop_menu_item =								new wxMenuItem(NULL, static_cast<int>(Command::STOP), "&��~\tF9");
	mp_stop_menu_item->Enable(false);

	Append(static_cast<int>(Command::OPEN_SETTING_WINDOW), "&�ݒ�E�B���h�E���J��\tCtrl+T");
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
	Append(static_cast<int>(Command::ABOUT), "&�o�[�W�������\tCtrl+Q");
	p_parent->Bind(wxEVT_MENU, &MainWindow::onAbout, p_parent, static_cast<int>(Command::ABOUT));
}