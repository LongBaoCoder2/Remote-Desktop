#include "NavigationBar.hpp"

ButtonNavigation::ButtonNavigation(wxWindow* parent,
    const wxPoint& pos,
    const wxSize& size)
    : wxPanel(parent, wxID_ANY, pos, size)
{
    // Create a vertical sizer for buttons
    ButtonSizer = new wxBoxSizer(wxVERTICAL);

    // Create a separator line
    auto separateLine = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(220, FromDIP(1)));
    separateLine->SetBackgroundColour(wxColour(229, 229, 229));
    ButtonSizer->Add(separateLine, 0, wxBOTTOM | wxALIGN_CENTER_HORIZONTAL, FromDIP(8));

    // Create navigation buttons
    auto HomeBtn = new Button(this, Window_ID::HOME_WINDOW, "HOME", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);
    auto MenuBtn = new Button(this, Window_ID::MENU_WINDOW, "MENU", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);
    auto ManagerBtn = new Button(this, Window_ID::MANAGE_WINDOW, "MANAGER", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);
    auto SettingBtn = new Button(this, Window_ID::SETTING_WINDOW, "SETTING", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);
    listButton = std::vector<Button>{
        HomeBtn,
        MenuBtn,
        ManagerBtn,
        SettingBtn
    };

    // Bind click events for the buttons
    for (auto button : listButton)
    {
        button->Bind(wxEVT_LEFT_DOWN, &ButtonNavigation::OnClick, this);
        ButtonSizer->Add(button, 0, wxTOP | wxALIGN_CENTER, FromDIP(5));
    }

    // Bind a specific click event for the SettingBtn
    SettingBtn->Bind(wxEVT_LEFT_DOWN, &ButtonNavigation::OnSettingClick, this, SettingBtn->GetId());
    this->SetSizerAndFit(ButtonSizer);
}

void ButtonNavigation::OnClick(wxMouseEvent& event) {
    const Window_ID eventID = static_cast<Window_ID>(event.GetId());

    for (auto& button : listButton) {
        if (button->GetId() != eventID) {
            button->SetSelected(false);
        }
        else {
            button->SetSelected(true);
        }
    }

    // Need code more
    this->GetParent()->OnNavigation()
}

void ButtonNavigation::OnSettingClick(wxMouseEvent& event) {
    wxMessageBox("Capture Frame activated");
    // Create and show the CaptureFrame
    CaptureFrame* captureFrame = new CaptureFrame(this->GetParent()->GetParent(), "Capture Window", wxDefaultPosition, wxDefaultSize);
    captureFrame->Show();
}
