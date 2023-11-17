#pragma once

#include "RoundedPanel.hpp"

class CustomDrawingPanel : public RoundedPanel {
public:
    CustomDrawingPanel(wxWindow* parent, const wxString& title, const wxString& subscription)
        : RoundedPanel(parent, title), titleText(title), subscriptionText(subscription) {
    }

    void DrawCustomContent(wxDC& dc) {
        // Set font style for the title
        wxFont titleFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        dc.SetFont(titleFont);

        // Draw the title
        dc.SetTextForeground(*wxBLACK);
        dc.DrawText(titleText, 20, 20);

        // Set font style for the subscription
        wxFont subFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        dc.SetFont(subFont);

        // Draw the subscription
        dc.DrawText(subscriptionText, 20, 60);
    }

private:
    wxString titleText;
    wxString subscriptionText;
};