#include "UserAddDialog.hpp"

UserAddDialog::UserAddDialog(wxWindow* parent, bool isAddUser, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style), isAddUser(isAddUser)
{
    auto IdText = new wxStaticText(this, wxID_ANY, "User Id: ");
    IDControl = new wxTextCtrl(this, wxID_ANY);
    auto IpText = new wxStaticText(this, wxID_ANY, "User IP Address: ");
    IPAddressControl = new wxTextCtrl(this, wxID_ANY);

    auto _btnMessage = isAddUser ? ("Add User") : ("Connect to user");
    SubmitBtn = new Button(this, wxID_ANY, _btnMessage, wxDefaultPosition, wxSize(150, 40));
    SubmitBtn->Bind(wxEVT_LEFT_DOWN, &UserAddDialog::OnSubmit, this);

    CloseButton = new Button(this, wxID_ANY, "Close", wxDefaultPosition, wxSize(150, 40));
    CloseButton->Bind(wxEVT_LEFT_DOWN, &UserAddDialog::OnCloseDialog, this);


    const auto marginVer = FromDIP(10);
    const auto marginHor = FromDIP(15);
    auto Sizer = new wxGridBagSizer(marginVer, marginHor);

    Sizer->Add(IdText, wxGBPosition(1, 1), { 1, 1 }, wxALIGN_RIGHT | wxEXPAND);
    Sizer->Add(IDControl, wxGBPosition(1, 2), { 1, 2 }, wxEXPAND | wxRIGHT, FromDIP(15));
    Sizer->Add(IpText, wxGBPosition(2, 1), { 1, 1 }, wxALIGN_RIGHT | wxEXPAND);
    Sizer->Add(IPAddressControl, wxGBPosition(2, 2), { 1, 2 }, wxEXPAND | wxRIGHT, FromDIP(15));

    Sizer->Add(SubmitBtn, wxGBPosition(3, 2), { 1 , 1 }, wxEXPAND | wxBOTTOM | wxRIGHT, FromDIP(20));
    Sizer->Add(CloseButton, wxGBPosition(3, 3), { 1 , 1 }, wxEXPAND | wxBOTTOM | wxRIGHT, FromDIP(20));

    this->SetSizerAndFit(Sizer);
}

void UserAddDialog::OnCloseDialog(wxMouseEvent& event)
{
    this->Close(true);
}

void UserAddDialog::OnSubmit(wxMouseEvent& event)
{
    std::string IPAddress = IPAddressControl->GetValue();
    std::string ID = IDControl->GetValue();

    if (isAddUser) {
        AddNewUserEvent evt(wxEVT_ADD_NEW_USER);
        evt.SetUserIPAddress(IPAddress);
        evt.SetUserID(ID);
        evt.SetEventObject(this);
        wxPostEvent(GetParent(), evt);
    }
    else {
        wxCommandEvent connectEvent(ConnectToUserEvent);
        connectEvent.SetClientData(new std::string(IPAddress));

        wxPostEvent(GetParent(), connectEvent);
    }

    this->Close(true);
}

UserAddDialog::~UserAddDialog()
{

}