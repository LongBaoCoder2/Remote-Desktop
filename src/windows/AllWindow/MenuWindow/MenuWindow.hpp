#pragma once

#include <wx/wx.h>

class MenuWindow : public wxWindow
{
public:

    MenuWindow(wxWindow* parent, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    ~MenuWindow();
};