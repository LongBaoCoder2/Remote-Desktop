#pragma once

#include <wx/wx.h>

class SettingWindow : public wxWindow
{
public:

    SettingWindow(wxWindow* parent, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    ~SettingWindow();
};