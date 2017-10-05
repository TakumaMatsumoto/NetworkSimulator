#include "App.h"
#include "MainWindow.h"

bool App::OnInit()
{
	mp_frame = new MainWindow();
	mp_frame->SetAutoLayout(true);
	mp_frame->Show();
	return true;
}
