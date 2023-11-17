#include "NavigationBar.hpp"

NavigationBar::NavigationBar(wxWindow* parent,
    wxWindowID id,
    MainFrame* MainParent,
    const wxPoint& pos,
    const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Dependency Injection MainFrame as Oservation
    this->MainParent = MainParent;

    // Create a vertical sizer for arranging elements
    NavSizer = new wxBoxSizer(wxVERTICAL);

    // Set the title
    auto TitleText = new wxStaticText(this, wxID_ANY, "Remote Desktop");
    TitleText->SetFont(wxFont(15, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    TitleText->SetForegroundColour(*wxWHITE);

    BtnNav = new NavigationButtons(this);

    // Create user icon and username information
    UserInfoPanel = new wxPanel(this, wxID_ANY);
    UserInfoPanel->SetWindowStyle(wxALIGN_BOTTOM);
    UserSizer = new wxBoxSizer(wxVERTICAL);
    wxImage iconImage("./assets/user_icon.png", wxBITMAP_TYPE_PNG);

    // Check image that is available
    if (iconImage.IsOk())
    {
        wxBitmap iconBitmap(iconImage.Rescale(64, 64));
        auto userBitmap = new wxStaticBitmap(UserInfoPanel, wxID_ANY, iconBitmap);
        UserSizer->Add(userBitmap, 0, wxALL, FromDIP(5));
    }

    auto userText = new wxStaticText(UserInfoPanel, wxID_ANY, "Username");
    UserSizer->Add(userText, 0, wxALIGN_CENTER | wxALL, FromDIP(5));
    UserInfoPanel->SetSizerAndFit(UserSizer);

    // Add elements to the NavSizer
    NavSizer->Add(TitleText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, FromDIP(25));
    NavSizer->Add(BtnNav, 0, wxEXPAND | wxTOP | wxBOTTOM, FromDIP(40));
    NavSizer->Add(UserInfoPanel, 0, wxALIGN_CENTER | wxTOP, FromDIP(60));

    // Set the background color for the NavigationBar
    this->SetBackgroundColour(CONFIG_UI::PRIMARY_DARK_COLOR);
    this->SetSizer(NavSizer);
}

NavigationBar::~NavigationBar()
{
}

void NavigationBar::OnNavigation(const Window_ID& Window_id)
{
    if (Window_id != this->currentID) {
        switch (Window_id)
        {
        case Window_ID::HOME_WINDOW:
            this->MainParent->CreateHomeWindow();
            break;

        case Window_ID::MANAGE_WINDOW:
            this->MainParent->CreateManageWindow();
            break;

        case Window_ID::MENU_WINDOW:
            this->MainParent->CreateMenuWindow();
            break;

        case Window_ID::SETTING_WINDOW:
            this->MainParent->CreateSettingWindow();
            break;
        }

        this->currentID = Window_id;
    }
}
