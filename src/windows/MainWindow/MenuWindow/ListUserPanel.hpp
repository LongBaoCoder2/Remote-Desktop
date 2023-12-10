#pragma once

#include <wx/wx.h>
#include <wx/gbsizer.h>
#include "../../components/Button.hpp"
#include "UserPanel.hpp"

class ListUserPanel : public wxPanel
{
public:
    ListUserPanel(wxWindow* parent,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize);
    ~ListUserPanel();

private:
    wxImage userIcon;
};