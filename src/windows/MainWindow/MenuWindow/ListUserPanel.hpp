#pragma once

#include <wx/wx.h>
#include <wx/gbsizer.h>
#include "../../components/Button.hpp"
#include "UserPanel.hpp"
#include "../../../models/ModelFactory.hpp"

class ListUserPanel : public wxPanel
{
public:
    ListUserPanel(wxWindow* parent,
        Admin* admin,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize);
    ~ListUserPanel();

    void UpdateListUserInfo();
private:
    Admin* pAdmin = nullptr;

    wxImage userIcon;
};