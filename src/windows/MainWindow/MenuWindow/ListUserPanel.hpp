#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>
#include "../../components/Button.hpp"
#include "UserPanel.hpp"
#include "../../../models/ModelFactory.hpp"
#include "UserAddDialog.hpp"

class ListUserPanel : public wxPanel
{
public:
    ListUserPanel(wxWindow* parent,
        Admin* admin,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize);
    ~ListUserPanel();

private:
    void UpdateListUserInfo();
    void OnAddUser(wxMouseEvent& event);
    void OnOpenConnect(wxMouseEvent& event);


    void OnAddNewUser(AddNewUserEvent& event);

private:
    Admin* pAdmin = nullptr;

    wxPanel* _UserPanels;
    wxFlexGridSizer* Sizer;
    wxImage userIcon;
    UserAddDialog* dialog = nullptr;
};