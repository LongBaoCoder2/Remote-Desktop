#include "NavigationButtons.hpp"

NavigationButtons::NavigationButtons(NavigationBar* parentBar,
    const wxPoint& pos,
    const wxSize& size)
    : wxPanel(parentBar, wxID_ANY, pos, size)
{
    // Dependency Injection NavigationBar as Observation
    this->parentBar = parentBar;

    // Create a vertical sizer for buttons
    ButtonSizer = new wxBoxSizer(wxVERTICAL);

    // Create a separator line
    auto separateLine = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(220, FromDIP(1)));
    separateLine->SetBackgroundColour(wxColour(229, 229, 229));
    ButtonSizer->Add(separateLine, 0, wxBOTTOM | wxALIGN_CENTER_HORIZONTAL, FromDIP(8));

    // Create navigation buttons
    // Bind click events for the buttons
    for (auto& button : listButton)
    {
        button->Bind(wxEVT_LEFT_DOWN, &NavigationButtons::OnClick, this);
        ButtonSizer->Add(button, 0, wxTOP | wxALIGN_CENTER, FromDIP(5));
    }

    // Bind a specific click event for the SettingBtn
    // SettingBtn->Bind(wxEVT_LEFT_DOWN, &NavigationButtons::OnSettingClick, this, SettingBtn->GetId());
    this->SetSizerAndFit(ButtonSizer);
}

void NavigationButtons::OnClick(wxMouseEvent& event) {
    const Window_ID eventID = static_cast<Window_ID>(static_cast<wxWindow*>(event.GetEventObject())->GetId());

    for (auto& button : listButton) {
        if (button->GetId() != eventID) {
            button->SetSelected(false);
        }
        else {
            button->SetSelected(true);
        }
    }


    // Need code more
    this->parentBar->OnNavigation(eventID);
    event.Skip();
}

// void NavigationButtons::OnSettingClick(wxMouseEvent& event) {
//     wxMessageBox("Capture Frame activated");
//     // Create and show the CaptureFrame
//     CaptureFrame* captureFrame = new CaptureFrame(nullptr, "Capture Window", wxDefaultPosition, wxDefaultSize);
//     captureFrame->Show();
// }
