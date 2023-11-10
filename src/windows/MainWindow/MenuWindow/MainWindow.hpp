#pragma once

#include <wx/wx.h>
#include "../../components/wButton.hpp"

class MainWindow : public wxWindow
{
public:
    MainWindow(wxWindow *parent, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    ~MainWindow();

private:
    void OnServerButtonClick(wxMouseEvent &);
};