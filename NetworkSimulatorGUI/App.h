#pragma once

class MyApp : public wxApp
{
	bool OnInit();
	wxFrame* mp_frame;
	wxSlider* mp_slider;
	wxStaticText* mp_time_label;
};
