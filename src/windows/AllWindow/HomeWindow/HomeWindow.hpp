#pragma once

#include <wx/wx.h>
// #include "../../components/RoundedText.hpp"
#include "../../constant.hpp"
#include "../../components/Button.hpp"
#include "../../MainWindow/NavigationBar/NavigationBar.hpp"

class NavigationBar;

class HomeWindow : public wxPanel
{
public:
    HomeWindow(wxWindow* parent, NavigationBar* navBar, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    ~HomeWindow();

private:
    NavigationBar* NavBar = nullptr;

    void OnClick(wxMouseEvent& event);
};