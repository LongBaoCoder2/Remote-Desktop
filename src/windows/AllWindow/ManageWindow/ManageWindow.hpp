#pragma once

#include <wx/wx.h>

class ManageWindow : public wxWindow
{
public:

    ManageWindow(wxWindow* parent, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    ~ManageWindow();
};