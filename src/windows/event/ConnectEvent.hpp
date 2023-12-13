#pragma once

#include <wx/event.h>

class AddNewUserEvent;

wxDECLARE_EVENT(wxEVT_ADD_NEW_USER, AddNewUserEvent);
wxDECLARE_EVENT(wxEVT_CONNECT_TO_SPECIFIC_USER, AddNewUserEvent);

wxDECLARE_EVENT(ConnectToUserEvent, wxCommandEvent);


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