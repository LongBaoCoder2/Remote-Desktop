#include "NavigationBar.hpp"

NavigationBar::NavigationBar(wxWindow* parent,
    wxWindowID id,
    const wxPoint& pos,
    const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    // Create a vertical sizer for arranging elements
    NavSizer = new wxBoxSizer(wxVERTICAL);

    // Set the title
    auto TitleText = new wxStaticText(this, wxID_ANY, "Remote Desktop");
    TitleText->SetFont(wxFont(15, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    TitleText->SetForegroundColour(*wxWHITE);


    BtnNav = new ButtonNavigation(this);

    // Create user icon and username information
    UserInfoPanel = new wxPanel(this, wxID_ANY);
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
    this->SetBackgroundColour(wxColour(17, 25, 38));
    this->SetSizer(NavSizer);
}

NavigationBar::~NavigationBar()
{
}
