#include "UserAddDialog.hpp"


UserAddDialog::UserAddDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    auto IdText = new wxStaticText(this, wxID_ANY, "User Id: ");
    IDControl = new wxTextCtrl(this, wxID_ANY);
    auto IpText = new wxStaticText(this, wxID_ANY, "User IP Address: ");
    IPAddressControl = new wxTextCtrl(this, wxID_ANY);
    SubmitBtn = new Button(this, wxID_ANY, "Add User", wxDefaultPosition, wxSize(250, 40));
    SubmitBtn->Bind(wxEVT_LEFT_DOWN, &UserAddDialog::OnAddUser, this);
    CloseButton = new Button(this, wxID_ANY, "Close", wxDefaultPosition, wxSize(250, 40));
    CloseButton->Bind(wxEVT_LEFT_DOWN, &UserAddDialog::OnCloseDialog, this);


    const auto marginVer = FromDIP(15);
    const auto marginHor = FromDIP(30);
    auto Sizer = new wxGridBagSizer(marginHor, marginVer);

    Sizer->Add(IdText, wxGBPosition(1, 1), { 1, 1 }, wxEXPAND);
    Sizer->Add(IDControl, wxGBPosition(1, 2), { 1, 2 }, wxEXPAND);
    Sizer->Add(IpText, wxGBPosition(2, 1), { 1, 1 }, wxEXPAND);
    Sizer->Add(IPAddressControl, wxGBPosition(2, 2), { 1, 2 }, wxEXPAND);

    Sizer->Add(SubmitBtn, wxGBPosition(3, 2), { 1 , 1 }, wxEXPAND);
    Sizer->Add(CloseButton, wxGBPosition(3, 3), { 1 , 1 }, wxEXPAND);

    this->SetSizerAndFit(Sizer);
}

void UserAddDialog::OnCloseDialog(wxMouseEvent& event)
{
    this->Close(true);
}

void UserAddDialog::OnAddUser(wxMouseEvent& event)
{

}

UserAddDialog::~UserAddDialog()
{

}