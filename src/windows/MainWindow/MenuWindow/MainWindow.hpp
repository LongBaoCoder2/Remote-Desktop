#pragma once

#include <wx/wx.h>
#include "../../components/Button.hpp"
#include "../ServerWindow/ServerWindow.hpp"
#include "../ClientWindow/ClientWindow.hpp"

class MainWindow : public wxWindow
{
public:
    MainWindow(wxWindow* parent, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

    ~MainWindow();

private:
    void OnServerButtonClick(wxMouseEvent&);
};