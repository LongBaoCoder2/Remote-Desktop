#include "ConnectEvent.hpp"

wxDEFINE_EVENT(wxEVT_ADD_NEW_USER, AddNewUserEvent);
wxDEFINE_EVENT(wxEVT_CONNECT_TO_SPECIFIC_USER, AddNewUserEvent);

wxDEFINE_EVENT(ConnectToUserEvent, wxCommandEvent);


AddNewUserEvent::AddNewUserEvent(wxEventType commandType, int id)
    : wxCommandEvent(commandType, id) {}

AddNewUserEvent::AddNewUserEvent(const AddNewUserEvent& event)
    : wxCommandEvent(event), ID(event.GetUserID()), IPAddress(event.GetUserIPAddress()) {}

wxEvent* AddNewUserEvent::Clone() const { return new AddNewUserEvent(*this); }

std::string AddNewUserEvent::GetUserID() const { return ID; }
void AddNewUserEvent::SetUserID(std::string Id) { this->ID = Id; }

std::string AddNewUserEvent::GetUserIPAddress() const { return IPAddress; }
void AddNewUserEvent::SetUserIPAddress(std::string IPAddress) { this->IPAddress = IPAddress; }
