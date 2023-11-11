#pragma once

#include <wx/wx.h>

class HomeWindow : public wxWindow
{
public:
    HomeWindow(wxWindow* parent, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    ~HomeWindow();
};