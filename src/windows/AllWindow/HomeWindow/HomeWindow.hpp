#pragma once

#include <wx/wx.h>
// #include "../../components/RoundedText.hpp"
#include "../../constant.hpp"

class HomeWindow : public wxPanel
{
public:
    HomeWindow(wxWindow* parent, const wxPoint& pos = wxDefaultPosition, const wxSize& size = CONFIG_UI::NORMAL_WINDOW - CONFIG_UI::NAVIGATION_SIZE);
    ~HomeWindow();
};