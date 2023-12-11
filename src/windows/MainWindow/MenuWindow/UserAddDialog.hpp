#pragma once

#include <wx/wx.h>
#include "../../components/Button.hpp"
#include <wx/gbsizer.h>

class AddNewUserEvent;

wxDECLARE_EVENT(wxEVT_ADD_NEW_USER, AddNewUserEvent);


class AddNewUserEvent : public wxCommandEvent
{
public:
    AddNewUserEvent(wxEventType commandType = wxEVT_ADD_NEW_USER, int id = 0);

    AddNewUserEvent(const AddNewUserEvent& event);

    wxEvent* Clone() const override;

    std::string GetUserID() const;
    void SetUserID(std::string ID);

    std::string GetUserIPAddress() const;
    void SetUserIPAddress(std::string IPAddress);

private:
    std::string ID;
    std::string IPAddress;
};



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