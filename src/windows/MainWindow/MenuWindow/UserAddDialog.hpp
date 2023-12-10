#pragma once

#include <wx/wx.h>
#include "../../components/Button.hpp"
#include <wx/gbsizer.h>

class UserAddDialog : public wxDialog
{
public:
    UserAddDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = "User Dialog", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);

    ~UserAddDialog();

private:
    void OnAddUser(wxMouseEvent& event);
    void OnCloseDialog(wxMouseEvent& event);

private:
    wxTextCtrl* IDControl;
    wxTextCtrl* IPAddressControl;
    Button* SubmitBtn, * CloseButton;
};