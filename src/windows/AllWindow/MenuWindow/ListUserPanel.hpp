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

    wxPanel* ListUserPanel::CreateHeaderPanel();
    wxPanel* ListUserPanel::CreateButtonPanel(wxWindow* parent, const wxString& addButtonLabel, const wxString& connectionButtonLabel);
    wxPanel* ListUserPanel::CreateSplitPanel();
    wxPanel* ListUserPanel::CreateUserPanels(const wxBitmap& userIcon);
};