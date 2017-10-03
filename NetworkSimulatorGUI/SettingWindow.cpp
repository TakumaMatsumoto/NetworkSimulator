#include "SettingWindow.h"

SettingWindow::SettingWindow(wxWindow * parent, wxWindowID id, const wxString & title,
	const wxPoint & position, const wxSize & size, long style)
	: wxDialog(parent, id, title, position, size, style)
{
	wxString dimensions = "", s;
	wxPoint p;
	wxSize  sz;

	sz.SetWidth(size.GetWidth() - 20);
	sz.SetHeight(size.GetHeight() - 70);

	p.x = 6; p.y = 2;
	s.Printf(_(" x = %d y = %d\n"), p.x, p.y);
	dimensions.append(s);
	s.Printf(_(" width = %d height = %d\n"), sz.GetWidth(), sz.GetHeight());
	dimensions.append(s);

	p.y += sz.GetHeight() + 10;
	wxButton * b = new wxButton(this, wxID_OK, _("OK"), p, wxDefaultSize);
	p.x += 110;
	wxButton * c = new wxButton(this, wxID_CANCEL, _("Cancel"), p, wxDefaultSize);
}

