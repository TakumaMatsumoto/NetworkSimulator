#include "Canvas.h"

BEGIN_EVENT_TABLE(Canvas, wxPanel)
// some useful events
/*
EVT_MOTION(Canvas::mouseMoved)
EVT_LEFT_DOWN(Canvas::mouseDown)
EVT_LEFT_UP(Canvas::mouseReleased)
EVT_RIGHT_DOWN(Canvas::rightClick)
EVT_LEAVE_WINDOW(Canvas::mouseLeftWindow)
EVT_KEY_DOWN(Canvas::keyPressed)
EVT_KEY_UP(Canvas::keyReleased)
EVT_MOUSEWHEEL(Canvas::mouseWheelMoved)
*/

// catch paint events
EVT_PAINT(Canvas::paintEvent)


END_EVENT_TABLE()

// some useful events
/*
void Canvas::mouseMoved(wxMouseEvent& event) {}
void Canvas::mouseDown(wxMouseEvent& event) {}
void Canvas::mouseWheelMoved(wxMouseEvent& event) {}
void Canvas::mouseReleased(wxMouseEvent& event) {}
void Canvas::rightClick(wxMouseEvent& event) {}
void Canvas::mouseLeftWindow(wxMouseEvent& event) {}
void Canvas::keyPressed(wxKeyEvent& event) {}
void Canvas::keyReleased(wxKeyEvent& event) {}
*/

Canvas::Canvas(wxFrame* parent) :
wxPanel(parent)
{
}

/*
* Called by the system of by wxWidgets when the panel needs
* to be redrawn. You can also trigger this call by
* calling Refresh()/Update().
*/

void Canvas::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

/*
* Alternatively, you can use a clientDC to paint on the panel
* at any time. Using this generally does not free you from
* catching paint events, since it is possible that e.g. the window
* manager throws away your drawing when the window comes to the
* background, and expects you will redraw it when the window comes
* back (by sending a paint event).
*
* In most cases, this will not be needed at all; simply handling
* paint events and calling Refresh() when a refresh is needed
* will do the job.
*/
void Canvas::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

/*
* Here we do the actual rendering. I put it in a separate
* method so that it can work no matter what type of DC
* (e.g. wxPaintDC or wxClientDC) is used.
*/
void Canvas::render(wxDC& dc)
{
	// draw some text
	dc.DrawText(wxT("Testing"), 40, 60);

	// draw a circle
	dc.SetBrush(*wxGREEN_BRUSH); // green filling
	dc.SetPen(wxPen(wxColor(255, 0, 0), 5)); // 5-pixels-thick red outline
	dc.DrawCircle(wxPoint(200, 100), 25 /* radius */);

	// draw a rectangle
	dc.SetBrush(*wxBLUE_BRUSH); // blue filling
	dc.SetPen(wxPen(wxColor(255, 175, 175), 10)); // 10-pixels-thick pink outline
	dc.DrawRectangle(300, 100, 400, 200);

	// draw a line
	dc.SetPen(wxPen(wxColor(0, 0, 0), 3)); // black line, 3 pixels thick
	dc.DrawLine(300, 100, 700, 300); // draw line across the rectangle

	// Look at the wxDC docs to learn how to draw other stuff
}