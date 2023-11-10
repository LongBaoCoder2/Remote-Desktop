#include "NavigationBar.hpp"

NavigationBar::NavigationBar(wxWindow *parent,
                             wxWindowID id,
                             const wxPoint &pos,
                             const wxSize &size)
    : wxPanel(parent, id, pos, size)
{
    NavSizer = new wxBoxSizer(wxVERTICAL);
    // NavbarPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);

    // Set title
    auto TitleText = new wxStaticText(this, wxID_ANY, "Remote Desktop");
    TitleText->SetFont(wxFont(15, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    TitleText->SetForegroundColour(*wxWHITE);

    // Button Sizer
    ButtonSizer = new wxBoxSizer(wxVERTICAL);
    BtnPanel = new wxPanel(this, wxID_ANY);

    // Button Navigation
    auto separateLine = new wxPanel(BtnPanel, wxID_ANY, wxDefaultPosition, wxSize(220, FromDIP(1)));
    separateLine->SetBackgroundColour(wxColour(229, 229, 229));
    separateLine->SetBackgroundColour(*wxWHITE);
    ButtonSizer->Add(separateLine, 0, wxBOTTOM | wxALIGN_CENTER_HORIZONTAL, FromDIP(8));

    auto HomeBtn = new wButton(BtnPanel, wxID_ANY, "HOME", wxDefaultPosition, wxSize(220, 38));
    auto MenuBtn = new wButton(BtnPanel, wxID_ANY, "MENU", wxDefaultPosition, wxSize(220, 38));
    auto ManagerBtn = new wButton(BtnPanel, wxID_ANY, "MANAGER", wxDefaultPosition, wxSize(220, 38));
    auto SettingBtn = new wButton(BtnPanel, wxID_ANY, "SETTING", wxDefaultPosition, wxSize(220, 38));
    std::vector<wButton *> listButton{
        HomeBtn,
        MenuBtn,
        ManagerBtn,
        SettingBtn};
    for (auto button : listButton)
    {
        button->Bind(wxEVT_LEFT_DOWN, &NavigationBar::OnClick, this);
        ButtonSizer->Add(button, 0, wxTOP | wxALIGN_CENTER, FromDIP(5));
    }
    // SettingBtn->Bind(wxEVT_LEFT_DOWN, &NavigationBar::OnSettingSelected, this);
    BtnPanel->SetSizerAndFit(ButtonSizer);

    // User Icon
    UserInfoPanel = new wxPanel(this, wxID_ANY);
    UserSizer = new wxBoxSizer(wxVERTICAL);
    wxImage iconImage("./assets/user_icon.png", wxBITMAP_TYPE_PNG);

    if (iconImage.IsOk())
    {
        wxBitmap iconBitmap(iconImage.Rescale(64, 64));
        auto userBitmap = new wxStaticBitmap(UserInfoPanel, wxID_ANY, iconBitmap);
        UserSizer->Add(userBitmap, 0, wxALL, FromDIP(5));
    }

    auto userText = new wxStaticText(UserInfoPanel, wxID_ANY, "Username");
    UserSizer->Add(userText, 0, wxALIGN_CENTER | wxALL, FromDIP(5));
    UserInfoPanel->SetSizerAndFit(UserSizer);

    NavSizer->Add(TitleText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, FromDIP(25));
    NavSizer->Add(BtnPanel, 0, wxEXPAND | wxTOP | wxBOTTOM, FromDIP(40));
    NavSizer->Add(UserInfoPanel, 0, wxALIGN_CENTER | wxTOP, FromDIP(60));

    this->SetBackgroundColour(wxColour(17, 25, 38));
    this->SetSizer(NavSizer);
}

NavigationBar::~NavigationBar()
{
}
