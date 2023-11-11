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
    auto HomeBtn = new Button(this, wxID_ANY, "HOME", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);
    auto MenuBtn = new Button(this, wxID_ANY, "MENU", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);
    auto ManagerBtn = new Button(this, wxID_ANY, "MANAGER", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);
    auto SettingBtn = new Button(this, wxID_ANY, "SETTING", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);
    std::vector<Button*> listButton{
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
    wxMessageBox("Button Click");
    event.Skip();
}

void ButtonNavigation::OnSettingClick(wxMouseEvent& event) {
    wxMessageBox("Capture Frame activated");
    // Create and show the CaptureFrame
    CaptureFrame* captureFrame = new CaptureFrame(this->GetParent()->GetParent(), "Capture Window", wxDefaultPosition, wxDefaultSize);
    captureFrame->Show();
}
